/*
 * RenderableForm.cpp
 *
 *  Created on: 18/gen/2011
 *  Author: Alkemist
 */

#include "Forms/RenderableForm.h"
#include "GL/GlCommons.h"
#include "GL/Util3D.h"

#define TIMER_INTERVAL_MS 10

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Runtime;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::System;
using namespace Osp::Graphics::Opengl;

RenderableForm::RenderableForm() {
}

RenderableForm::~RenderableForm() {
}

bool RenderableForm::OnStart() {
    AppLog("RenderableForm::OnStart() [Starting render thread]");

    InitEGL();
    InitGL();

    OnStartRendering();

    _timer = new Timer();
    _timer->Construct(*this);
    _timer->Start(TIMER_INTERVAL_MS);

    return true;
}

void RenderableForm::OnStop() {
    AppLog("RenderableForm::OnStop() [Stopping render thread]");

    DestroyGL();

    _timer->Cancel();
    delete _timer;

    OnStopRendering();

}

result RenderableForm::OnInitializing(void) {
    result r = E_SUCCESS;
    StartRendering();
    return r;
}

result RenderableForm::OnTerminating(void) {
    result r = E_SUCCESS;
    StopRendering();
    return r;
}

void RenderableForm::StartRendering() {
    AppLog("RenderableForm::StartRendering()");
    Thread::Construct(THREAD_TYPE_EVENT_DRIVEN);
    this->Start();
}

void RenderableForm::StopRendering() {
    AppLog("RenderableForm::StopRendering()");
    this->Stop();
    this->Join();
}

void RenderableForm::InitEGL() {
    AppLog("RenderableForm::InitEGL()");

    eglBindAPI(EGL_OPENGL_ES_API);
    AppAssertf(EGL_SUCCESS == eglGetError(), "eglBindAPI failed");

    EGLint numConfigs = 1;

    EGLint eConfigList[] = {
            EGL_RED_SIZE, 5, // Comment disables code formatter
            EGL_GREEN_SIZE, 6, // Comment disables code formatter
            EGL_BLUE_SIZE, 5, // Comment disables code formatter
            EGL_ALPHA_SIZE, 0, // Comment disables code formatter
            EGL_DEPTH_SIZE, 8, // Comment disables code formatter
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT, // Comment disables code formatter
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT, // Comment disables code formatter
            EGL_NONE // Comment disables code formatter
            };

    eDisplay = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY);
    AppAssertf(EGL_SUCCESS == eglGetError(), "eDisplay failed");

    eglInitialize(eDisplay, NULL, NULL);
    AppAssertf(EGL_SUCCESS == eglGetError(), "eglInitialize failed");

    eglChooseConfig(eDisplay, eConfigList, &eConfig, 1, &numConfigs);
    AppAssertf(EGL_SUCCESS == eglGetError(), "eglChooseConfig failed");

    eSurface = eglCreateWindowSurface(eDisplay, eConfig, (EGLNativeWindowType) this, null);
    AppAssertf(EGL_NO_SURFACE != eSurface && EGL_SUCCESS == eglGetError(), "eglCreateWindowSurface failed");

    eContext = eglCreateContext(eDisplay, eConfig, EGL_NO_CONTEXT, null);
    AppAssertf(EGL_SUCCESS == eglGetError(), "eglCreateContext failed");

    eglMakeCurrent(eDisplay, eSurface, eSurface, eContext);
    AppAssertf(EGL_SUCCESS == eglGetError(), "eglMakeCurrent failed");

}

void RenderableForm::InitGL() {
    AppLog("RenderableForm::InitGL()");

    int x = 0, y = 0, width = 0, height = 0;
    // get the width & height of the screen
    Application::GetInstance()->GetAppFrame()->GetFrame()->GetBounds(x, y, width, height);

    AppLog("RenderableForm: View bounds: %d %d %d %d", x, y, width, height);

    glViewport(x, y, width, height);
    GL_ASSERT("glViewport");

    glClearDepthf(1.0f);
    GL_ASSERT("glClearDepthf");

    glDepthFunc(GL_LEQUAL);
    GL_ASSERT("glDepthFunc");

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    GL_ASSERT("glHint");

    glDepthMask(GL_TRUE);
    GL_ASSERT("glDepthMask");

    glEnable(GL_DEPTH_TEST);
    GL_ASSERT("glEnable(GL_DEPTH_TEST)");

    float fWidth = width;
    float fHeight = height;
    gluPerspective(45.0, fWidth / fHeight, 1, 100);
    GL_ASSERT("gluPerspective()");

}

void RenderableForm::DestroyGL() {
    if (eDisplay) {
        eglMakeCurrent(eDisplay, null, null, null);

        if (eContext) {
            eglDestroyContext(eDisplay, eContext);
            eContext = EGL_NO_CONTEXT;
        }

        if (eSurface) {
            eglDestroySurface(eDisplay, eSurface);
            eSurface = EGL_NO_SURFACE;
        }

        eglTerminate(eDisplay);
        eDisplay = EGL_NO_DISPLAY;
    }
}

void RenderableForm::OnTimerExpired(Osp::Base::Runtime::Timer & timer) {
    _timer->Start(TIMER_INTERVAL_MS);
    OnDrawFrame();
    eglSwapBuffers(eDisplay, eSurface);
}
