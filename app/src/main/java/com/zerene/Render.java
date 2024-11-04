package com.zerene;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class Render extends GLSurfaceView implements GLSurfaceView.Renderer {

    public int screen_width;
    public int screen_height;

    public Render(Context context) {
        super(context);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        getHolder().setFormat(PixelFormat.TRANSLUCENT);
        setEGLContextClientVersion(3);
        setRenderer(this);
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int i, int i1) {
        screen_width = i;
        screen_height = i1;
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        Main.onDrawFrame(screen_width,screen_height);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        Main.onTouchEvent(event);
        return super.onTouchEvent(event);
    }
}
