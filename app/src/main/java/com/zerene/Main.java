package com.zerene;

import android.app.Activity;
import android.content.Context;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.WindowManager;
import java.util.Objects;

public class Main {

    static {
        System.loadLibrary("zerene");
    }

    public static native void onDrawFrame(int width,int height);

    public static native void onTouchEvent(MotionEvent event);

    public static void Start(Context context) {
        WindowManager windowManager = ((Activity)context).getWindowManager();
        WindowManager.LayoutParams params = new WindowManager.LayoutParams();
        params.type = WindowManager.LayoutParams.TYPE_APPLICATION;
        params.flags = WindowManager.LayoutParams.FLAG_FULLSCREEN;
        params.flags |= WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN;
        params.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
        params.flags |= WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL;
        if (!Objects.equals(context.getPackageName(),"com.zerene")) {
            params.flags |= WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE;
        }
        params.gravity = Gravity.START;
        params.gravity |= Gravity.TOP;
        params.x = 0;
        params.y = 0;
        windowManager.addView(new Render(context),params);
    }

}
