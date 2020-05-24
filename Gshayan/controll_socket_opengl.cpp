#include "controll_socket_opengl.h"


//
// void controll_socket_opengl::error_callback(int error, const char* description)
//{
//    fprintf(stderr, "Error %d: %s\n", error, description);
//}
//
//int controll_socket_opengl::imgui()
//{
//    // Setup window
// //   glfwSetErrorCallback(error_callback);
//    if (!glfwInit())
//        return 1;
//    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL2 example", NULL, NULL);
//    glfwMakeContextCurrent(window);
//    glfwSwapInterval(1); // Enable vsync
//
//    // Setup ImGui binding
//    ImGui_ImplGlfwGL2_Init(window, true);
//
//    // Setup style
//    ImGui::StyleColorsClassic();
//    //ImGui::StyleColorsDark();
//
//    // Load Fonts
//    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. 
//    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. 
//    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
//    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
//    // - Read 'extra_fonts/README.txt' for more instructions and details.
//    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
//    //ImGuiIO& io = ImGui::GetIO();
//    //io.Fonts->AddFontDefault();
//    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/Roboto-Medium.ttf", 16.0f);
//    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/Cousine-Regular.ttf", 15.0f);
//    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/DroidSans.ttf", 16.0f);
//    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyTiny.ttf", 10.0f);
//    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
//    //IM_ASSERT(font != NULL);
//
//    bool show_demo_window = true;
//    bool show_another_window = false;
//    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//
//    // Main loop
//    while (!glfwWindowShouldClose(window))
//    {
//        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
//        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
//        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
//        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
//        glfwPollEvents();
//        ImGui_ImplGlfwGL2_NewFrame();
//
//        // 1. Show a simple window.
//        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
//        {
//            static float f = 0.0f;
//            ImGui::Text("Hello, world!");                           // Some text (you can use a format string too)
//            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float as a slider from 0.0f to 1.0f
//            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats as a color
//            if (ImGui::Button("Demo Window"))                       // Use buttons to toggle our bools. We could use Checkbox() as well.
//                show_demo_window ^= 1;
//            if (ImGui::Button("Another Window"))
//                show_another_window ^= 1;
//            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//        }
//
//        // 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name the window.
//        if (show_another_window)
//        {
//            ImGui::Begin("Another Window", &show_another_window);
//            ImGui::Text("Hello from another window!");
//            ImGui::End();
//        }
//
//        // 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow().
//        if (show_demo_window)
//        {
//            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
//            ImGui::ShowDemoWindow(&show_demo_window);
//        }
//
//        // Rendering
//        int display_w, display_h;
//        glfwGetFramebufferSize(window, &display_w, &display_h);
//        glViewport(0, 0, display_w, display_h);
//        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
//        glClear(GL_COLOR_BUFFER_BIT);
//        //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
//        ImGui::Render();
//        glfwSwapBuffers(window);
//    }
//
//    // Cleanup
//    ImGui_ImplGlfwGL2_Shutdown();
//    glfwTerminate();
//
//    return 0;
//}
//


controll_socket_opengl::controll_socket_opengl()
{
	cout << "time=" << time(NULL)<<endl;
//	imgui();
	osg = new Osgtest01();
	if (decklinkactive) {
		dckLinkKeyerDelegate = new  DeckLinkKeyerDelegate();

		if(dckLinkKeyerDelegate->decklinkIsok){
		dckLinkKeyerDelegate->m_videoFrameGdi->GetBytes((void**)&pbDestData);
		osg->viewWidth = dckLinkKeyerDelegate->m_videoFrameGdi->GetWidth();
		osg->viewHeight = dckLinkKeyerDelegate->m_videoFrameGdi->GetHeight();
		}
		else {
			decklinkactive = false;
		}
	}
	osg->building();
sockets1.setOsgtest01(osg);

	

	thread start (&soceketS1::connectAnd ,&sockets1);

	masterLoop();


}


void controll_socket_opengl::masterLoop()
{


	//int timeduration = 38500;
	int timeduration = 19000;
	start_tick = osg::Timer::instance()->time_u();
	//cout << "decklink22222..osg->image2.get()=" << osg->image2 << endl;
	//cout << "decklink22222.. dckLinkKeyerDelegate->m_videoFrameGdi=" << dckLinkKeyerDelegate->m_videoFrameGdi << endl;
	while (osg->_viewer->isRealized()) {
		 start_tick = osg::Timer::instance()->time_u();
		
		 //else while (k <= 0) {
			// k = k + timeduration;
			// start_tick = start_tick + timeduration;
		 //}



		if (sockets1.newSettingpack) {
			osg::Timer_t time0 = osg::Timer::instance()->time_u();

			//cout << "980220  masterLoop-" << 4 << endl;
			if (sockets1.settingp.exit == 13) exit(0);
			osg->updatesettingpack(sockets1.settingp);
			//cout << "980220  masterLoop-" << 6 << endl;
			osg->updateControolgpack(sockets1.controolp);
			//cout << "980220  masterLoop-" << 7 << endl;
			sockets1.packUpdatedProcess();
			//cout << "980220  masterLoop-" << 8 << endl;
			cout << "990220-update setting or pack at  " << (osg::Timer::instance()->time_u() - time0) / 1000000 << endl;

		}


		if (decklinkactive) {
		//	pOpenGLOutput->RenderToDevice();
			//cout << "decklink22222111111..osg->image2.get()=" << osg->image2 << endl;
		
			

			osg->runframe2();
			//osg->runframe3(pbDestData);
			//osg->image2->allocateImage(720, 576, 1, GL_BGRA, GL_UNSIGNED_BYTE);
			osg->image2->allocateImage(1920, 1080, 1, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8);
		//	cout << "decklink22222444444..osg->image2.get()=" << osg->image2 << "\t size" << dckLinkKeyerDelegate->theFrameBMIsize << "\t  row" << osg->image2->getRowSizeInBytes() << "\t  allocat" << osg->image2->getAllocationMode() <<endl;
			// get frame buffer pointer
			memcpy(pbDestData, osg->image2->getDataPointer(),  dckLinkKeyerDelegate->theFrameBMIsize);//   100000);//
			dckLinkKeyerDelegate->deckLinkOutput->DisplayVideoFrameSync(dckLinkKeyerDelegate->m_videoFrameGdi);

			
		}
		else {
osg->runframe2();
//x++;
//std::string s = "c:\\sss\\MahanRASA" + std::to_string(x) + ".png";
//osg->image2->allocateImage(720, 576, 1, GL_BGRA, GL_UNSIGNED_BYTE);
//osgDB::writeImageFile(*osg->image2, s);
		}


		//x++;
		//	std::string s = "c:\\sss\\MahanRASA" + std::to_string(x) + ".png";
		////osg->image2->allocateImage(720, 576, 1, GL_ARGB, GL_UNSIGNED_BYTE);
		//if (x > 100) {
		//	cout << "   ************************************ ";
		//	x = 0;
		//	osgDB::writeImageFile(*osg->image2, s);
		//}
		//cout << "  bybshayan  x=" << x << endl;


		start_tick = start_tick + timeduration;
		int k = -osg::Timer::instance()->time_u() + start_tick;
		//std::cout << "k=" << k<<"      timeu="<<(osg::Timer::instance()->time_u()/10000 ) << "      timet=" << (osg::Timer::instance()->tick() / 10000) << std::endl;
		if (k>0)OpenThreads::Thread::microSleep(k);
		else while (k <= 0) {
		 k = k + timeduration;
		 start_tick = start_tick + timeduration;
		}

	}
}

controll_socket_opengl::~controll_socket_opengl()
{
}

