#include <jni.h>
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_android.h"
#include "Imgui/imgui_impl_opengl3.h"
#include <android/log.h>
#include <android/asset_manager.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <string>

static bool g_Initialized;

static void onDrawFrame(JNIEnv *env, jclass clazz, jint width, jint height) {

    if (!g_Initialized) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        ImGui::StyleColorsClassic();

        ImGui_ImplAndroid_Init(nullptr);
        ImGui_ImplOpenGL3_Init("#version 300 es");
        io.Fonts->AddFontFromFileTTF("/system/fonts/DroidSans.ttf", 22.0f);
        ImGui::GetStyle().ScaleAllSizes(3.0f);
        g_Initialized = true;
    }
    ImGuiIO& io = ImGui::GetIO();

    static bool show_demo_window = true;
    static bool show_another_window = false;
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.00f);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(width,height);
    ImGui::NewFrame();

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello world"); // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }

    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

static void onTouchEvent(JNIEnv *env, jclass clazz, jobject event) {
    jclass MotionEvent = env->GetObjectClass(event);
    jfloat x = env->CallFloatMethod(event,env->GetMethodID(MotionEvent, "getX", "()F"));
    jfloat y = env->CallFloatMethod(event,env->GetMethodID(MotionEvent,"getY", "()F"));
    jint action = env->CallIntMethod(event,env->GetMethodID(MotionEvent, "getAction", "()I"));
    ImGuiIO& io = ImGui::GetIO();
    if (action == 0)
        io.MouseDown[0] = true;
    else if (action == 1)
        io.MouseDown[0] = false;
    io.MousePos[0] = x;
    io.MousePos[1] = y;
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {

    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);

    JNINativeMethod methods[] = {
            {"onDrawFrame","(II)V", reinterpret_cast<void *>(onDrawFrame)},
            {"onTouchEvent","(Landroid/view/MotionEvent;)V", reinterpret_cast<void *>(onTouchEvent)},
    };

    jclass clazz = env->FindClass("com/zerene/Main");
    if (env->RegisterNatives(clazz,methods,sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;

    return JNI_VERSION_1_6;
}


