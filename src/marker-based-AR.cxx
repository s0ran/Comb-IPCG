// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow* window;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <opencv2/opencv.hpp>
using namespace glm;
using namespace std;
using namespace cv;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <opencv2/highgui.hpp>

int WIDTH=512/2;
int HEIGHT=394/2;

bool CV2GLM(const Mat& cvmat, mat4* glmmat) {
    memcpy(value_ptr(*glmmat), cvmat.data, 16 * sizeof(float));
    *glmmat = transpose(*glmmat);
    return true;
}

bool GLM2CV(const mat4& glmmat, Mat* cvmat) {
    if (cvmat->cols != 4 || cvmat->rows != 4) {
        (*cvmat) = cv::Mat(4, 4, CV_32F);
    }
    memcpy(cvmat->data, value_ptr(glmmat), 16 * sizeof(float));
    *cvmat = cvmat->t();
    return true;
}

int initialize_window(){
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, 0);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( WIDTH, HEIGHT, "Unvisable", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	//glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    //glfwSetCursorPos(window, 1024/4, 768/4);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	return 0;
}

int load_obj(vector<vec3>& vertices,GLuint &vertexbuffer,GLuint &uvbuffer,GLuint& normalbuffer){
	// Read our .obj file
	
	vector<vec2> uvs;
	vector<vec3> normals;
	bool res = loadOBJ("suzanne.obj", vertices, uvs, normals);

	// Load it into a VBO

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	return 0;
}

void set_buffers(GLuint &vertexbuffer,GLuint &uvbuffer,GLuint& normalbuffer){
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
}

bool checkChess(Mat& image,Size chessSize,vector<Point2f>& imagepoint){
    Mat gray;
    
    cvtColor(image,gray,COLOR_BGR2GRAY);
    bool success=findChessboardCorners(image,chessSize,imagepoint, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);
    //cout<<success<<endl;
    if (success){
        Size winSize = Size( 5, 5 );
        Size zeroZone = Size( -1, -1 );
        TermCriteria criteria = TermCriteria( TermCriteria::EPS + TermCriteria::COUNT, 40, 0.001 );
        cornerSubPix(gray, imagepoint, winSize, zeroZone, criteria );
        
        //drawChessboardCorners(image, chessSize, imagepoint, success);
    }
    return success;
}

void compute_MVP(GLuint MatrixID,GLuint ViewMatrixID,GLuint ModelMatrixID){
	// Compute the MVP matrix from keyboard and mouse input
	// computeMatricesFromInputs();
	//mat4 ProjectionMatrix = getProjectionMatrix(); 
	mat4 ProjectionMatrix = perspective(radians(45.0f), (float) WIDTH / HEIGHT, 0.1f, 100.0f);
	//mat4 ViewMatrix = getViewMatrix();
	mat4 ViewMatrix = lookAt(vec3(0,0,5), vec3(0,0,0), vec3(0,1,0));
	mat4 ModelMatrix = mat4(1.0);
	mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
}

bool drawArrow(Mat& image,vector<Point3f> src,vector<Point3f> dist, Mat rvec, Mat tvec,Mat cameraMatrix,Mat distCoeffs,Scalar color){
    vector<Point2f> srcPoint,distPoint;
    projectPoints(Mat(src),rvec,tvec,cameraMatrix,distCoeffs,srcPoint);
    projectPoints(Mat(dist),rvec,tvec,cameraMatrix,distCoeffs,distPoint);
    arrowedLine(image,srcPoint[0],distPoint[0],color,5);
    return true;
}


int main( void )
{
	Size chessSize = Size(7,7);
	Mat frame;
    VideoCapture cap=VideoCapture(0);
	Mat cameraMatrix, R,T,distCoeffs;
	Size frameSize,objectSize;
	vector<Point3f> centor;
	vector<Point2f> imagepoint,centorpoint;
    vector<Point3f> objectpoint;


	centor.push_back(Point3f(3,3,0));
	for(int i=0;i<chessSize.width;i++){
        for(int j=0;j<chessSize.height;j++){
            objectpoint.push_back(Point3f(j,i,0));
        }
    }
	
	initialize_window();
	if (cap.isOpened()){
        cout<<"success to open the camera"<<endl;
    }else{
        cout<<"failed to open the camera"<<endl;
        return -1;
    }

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

	// Load the texture
	GLuint Texture = loadDDS("uvmap.DDS");
	
	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
	vector<vec3> vertices;
	GLuint vertexbuffer,uvbuffer,normalbuffer;
	load_obj(vertices,vertexbuffer,uvbuffer,normalbuffer);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	namedWindow("marker-based-AR");
	resizeWindow("marker-based-AR", WIDTH, HEIGHT);

	while (true){
		cap>>frame;
		int k=waitKey(1)&0xFF;
        if (k==27){
            cap.release();
            break;
        }
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		if (checkChess(frame,chessSize,imagepoint)){
			frameSize=Size(frame.rows,frame.cols);
            vector<vector<Point2f> > imagepoints{imagepoint};
            vector<vector<Point3f> > objectpoints{objectpoint};
            Mat rvec,tvec;
            calibrateCamera(InputArrayOfArrays(objectpoints), InputArrayOfArrays(imagepoints), frameSize, cameraMatrix, distCoeffs, R, T);
            solvePnP(Mat(objectpoint),Mat(imagepoint),cameraMatrix,distCoeffs,rvec,tvec);
			projectPoints(Mat(centor),rvec,tvec,cameraMatrix,distCoeffs,centorpoint);
			Mat rotation;
			//cout<<rvec<<endl;
			//Rodrigues(rvec, rotation);
			//cout<<rotation<<endl;
			compute_MVP(MatrixID,ViewMatrixID,ModelMatrixID);
			vec3 lightPos = vec3(4,4,4);
			glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

			// Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture);
			// Set our "myTextureSampler" sampler to use Texture Unit 0
			glUniform1i(TextureID, 0);
			set_buffers(vertexbuffer,uvbuffer,normalbuffer);
			// Draw the triangles !
			glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);

			// Swap buffers
			glfwSwapBuffers(window);
			glfwPollEvents();

			glReadBuffer(GL_FRONT);
			Mat object = Mat(Size(WIDTH*2, HEIGHT*2), CV_8UC4);
			glReadPixels(0, 0, WIDTH*2, HEIGHT*2, GL_BGRA_EXT, GL_UNSIGNED_BYTE, object.data);
			flip(object, object, 0); 
			cvtColor(frame,frame,COLOR_BGR2BGRA);
			objectSize=Size(object.cols, object.rows);
			Mat roi = frame(Rect2f(centorpoint[0].x-WIDTH,centorpoint[0].y-HEIGHT,object.cols,object.rows));

			Mat channels[4];
			split(object,channels);
			object.copyTo(roi,channels[0]+channels[1]+ channels[2]+ channels[3]);
		}
		imshow("marker-based-AR",frame);
	} 

	destroyWindow("marker-based-AR");
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

