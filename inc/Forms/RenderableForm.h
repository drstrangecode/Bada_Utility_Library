/*
 * RenderableForm.h
 *
 *  Created on: 18/gen/2011
 *      Author: Alkemist
 */

#ifndef RENDERABLEFORM_H_
#define RENDERABLEFORM_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>
#include <FGraphicsOpengl.h>
#include <FGraphicsOpengl2.h>

class RenderableForm: public Osp::Ui::Controls::Form,
        public Osp::Base::Runtime::Thread,
        public Osp::Base::Runtime::ITimerEventListener {

    public:
        RenderableForm();
        virtual ~RenderableForm();

    public:
        void OnTimerExpired(Osp::Base::Runtime::Timer & timer);
        virtual result OnInitializing(void);
        virtual result OnTerminating(void);

    private:

        void InitEGL();
        void InitGL();
        void InitLights();
        void DestroyGL();

        Osp::Graphics::Opengl::EGLDisplay eDisplay;
        Osp::Graphics::Opengl::EGLSurface eSurface;
        Osp::Graphics::Opengl::EGLConfig eConfig;
        Osp::Graphics::Opengl::EGLContext eContext;

        Osp::Base::Runtime::Timer * _timer;

    private:
        void StartRendering();
        void StopRendering();

    protected:

        virtual void OnStartRendering() = 0;
        virtual void OnStopRendering() = 0;
        virtual void OnDrawFrame() = 0;

    public:
        bool OnStart(void);
        void OnStop(void);

};

#endif /* RENDERABLEFORM_H_ */
