#ifndef RE_CAMERA_H
#define RE_CAMERA_H

// Pan the camera around with WASD
void MoveCamera2DWithKeyboard(Camera2D* cam, float speed);

// Zoom the camera in and out with KEY_PAGE_UP and KEY_PAGE_DOWN
void ZoomCamera2DWithKeyboard(Camera2D* cam, float zoomSpeed);

#endif // !RE_CAMERA_H
