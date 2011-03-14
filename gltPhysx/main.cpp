/***********************************************
 * main.cpp
 * @author - Kenichi Yorozu
 * @email - rozken@gmail.com
 * @website - http://rozken.homelinux.net/
 * @description - Entry Point for Debugging and Using gltPhysX.hpp.
 * @descrition - This Project is  creating a Object-Oriented Physics-Based 
 * Simulation Circumstance using Nvidia PhysX with OpenGL Toolkit (GLT).
 * @notice - Sourcefiles on this repository is provided as-is and no guarentee 
 * or warrenty is provided for any damage that may arise from using it. 
 * This code is free for your own use, the only thing I ask is a small 
 * credit somewhere for my work. An e-mail saying you found it useful 
 * would also be much appreciated by myself.
 ***********************************************/

#include "gltPhysX.hpp"		//use Physics-Based Environment

using namespace std;

	/*
	 * GlutMain : Entry Point for this Program
	 * @return bool - whether program ended correctly or not.
	 */
bool GlutMain(const std::vector<std::string> &arg)
{
	GlutWindow *main = new gltPhysX(800,600,100,100);
	main->open();
	cout << "===Viewport Navigation (Maya Style)===" <<endl;
	cout << "Rotate: Right Drag" << endl;
	cout << "Move: Cener Drag" << endl;
	cout << "Zoom: Right and Center Drag" << endl;
	cout << "===Simulation Navigation===" << endl;
	cout << "Simulation ON/OFF: Space Key" << endl;
	return true;
}