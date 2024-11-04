# Inject mod
In your game MainActivity
```smali
# onCreate
invoke-static {p0}, Lcom/zerene/Main;->Start(Landroid/content/Context;)V
```
If unity game
find com.unity3d.player.UnityPlayer in smali
```smali
# injectEvent
invoke-super {p0, p1}, Landroid/opengl/GLSurfaceView;->onTouchEvent(Landroid/view/MotionEvent;)Z
```
