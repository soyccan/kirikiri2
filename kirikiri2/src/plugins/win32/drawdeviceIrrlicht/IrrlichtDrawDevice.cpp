#include <windows.h>
#include "IrrlichtDrawDevice.h"
#include "LayerManagerInfo.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

extern void message_log(const char* format, ...);
extern void error_log(const char *format, ...);

/**
 * �R���X�g���N�^
 */
LayerManagerInfo::LayerManagerInfo(ITexture *texture) : texture(texture)
{
	destBuffer = NULL;
};

/**
 * �f�X�g���N�^
 */
LayerManagerInfo::~LayerManagerInfo()
{
}


/**
 * �e�N�X�`�������b�N���ĕ`��̈�����擾����
 */
void
LayerManagerInfo::lock()
{
	if (texture) {
		destBuffer = (unsigned char *)texture->lock();
		core::dimension2d<s32> size = texture->getSize();
		destWidth  = size.Width;
		destHeight = size.Height;
		destPitch  = texture->getPitch();
	} else {
		destBuffer = NULL;
	}
}

/**
 * ���b�N���ꂽ�e�N�X�`���Ƀr�b�g�}�b�v�`����s��
 */
void
LayerManagerInfo::copy(tjs_int x, tjs_int y, const void * bits, const BITMAPINFO * bitmapinfo,
					   const tTVPRect &cliprect, tTVPLayerType type, tjs_int opacity)
{
	// bits, bitmapinfo �ŕ\�����r�b�g�}�b�v�� cliprect �̗̈���Ax, y �ɕ`�悷��B

	if (destBuffer) {
		int srcPitch = -bitmapinfo->bmiHeader.biWidth * 4; // XXX ���߂���
		unsigned char *srcBuffer = (unsigned char *)bits - srcPitch * (bitmapinfo->bmiHeader.biHeight - 1);
		int srcx   = cliprect.left;
		int srcy   = cliprect.top;
		int width  = cliprect.get_width();
		int height = cliprect.get_height();
		// �N���b�s���O
		if (x < 0) {
			srcx  += x;
			width += x;
			x = 0;
		}
		if (x + width > destWidth) {
			width -= ((x + width) - destWidth);
		}
		if (y < 0) {
			srcy += y;
			height += y;
			y = 0;
		}
		if (y + height > destHeight) {
			height -= ((y + height) - destHeight);
		}
		unsigned char *src  = srcBuffer  + srcy * srcPitch  + srcx * 4;
		unsigned char *dest = destBuffer +    y * destPitch +    x * 4;
		for (int i=0;i<height;i++) {
			memcpy(dest, src, width * 4);
			src  += srcPitch;
			dest += destPitch;
		}
	}
}

/**
 * �e�N�X�`���̃��b�N�̉���
 */
void
LayerManagerInfo::unlock()
{
	if (texture) {
		texture->unlock();
		destBuffer = NULL;
	}
}

/**
 * �R���X�g���N�^
 */
tTVPIrrlichtDrawDevice::tTVPIrrlichtDrawDevice()
{
	device = NULL;
}

/**
 * �f�X�g���N�^
 */
tTVPIrrlichtDrawDevice::~tTVPIrrlichtDrawDevice()
{
	detach();
}

/**
 * �e�N�X�`���̊��蓖��
 * @param manager ���C���}�l�[�W��
 */
void 
tTVPIrrlichtDrawDevice::allocInfo(iTVPLayerManager * manager)
{
	if (device) {
		video::IVideoDriver* driver = device->getVideoDriver();

		// �e�N�X�`�����蓖��XXX �T�C�Y���肪�K�v�c
		ITexture *texture = driver->addTexture(core::dimension2d<s32>(1024, 1024), "layer", ECF_A8R8G8B8);
		if (texture == NULL) {
			TVPThrowExceptionMessage(L"�e�N�X�`���̊��蓖�ĂɎ��s���܂���");
		}

		manager->SetDrawDeviceData((void*)new LayerManagerInfo(texture));

		// �X�V�v��
		tjs_int w, h;
		if (manager->GetPrimaryLayerSize(w, h)) {
			manager->RequestInvalidation(tTVPRect(0,0,w,h));
		}
	}
}

/**
 *  �e�N�X�`���̉��
 * @param manager ���C���}�l�[�W��
 */
void
tTVPIrrlichtDrawDevice::freeInfo(iTVPLayerManager * manager)
{
	if (device) {
		LayerManagerInfo *info = (LayerManagerInfo*)manager->GetDrawDeviceData();
		if (info != NULL) {
			video::IVideoDriver* driver = device->getVideoDriver();
			driver->removeTexture(info->texture);
			manager->SetDrawDeviceData(NULL);
			delete info;
		}
	}
}

/**
 * �f�o�C�X�̐���
 * @param hwnd �n���h��
 * @param �h���C�o�̎��
 */
static IrrlichtDevice *
create(HWND hwnd, irr::video::E_DRIVER_TYPE type, irr::IEventReceiver *receiver)
{
	SIrrlichtCreationParameters params;
	params.WindowId     = reinterpret_cast<s32>(hwnd);
	params.DriverType    = type;
	params.Bits          = 32;
	params.Stencilbuffer = true;
	params.Vsync = true;
	params.EventReceiver = receiver;
	return createDeviceEx(params);
}

/**
 * �E�C���h�E�̍Đݒ�
 * @param hwnd �n���h��
 */
void
tTVPIrrlichtDrawDevice::attach(HWND hwnd)
{
	// �f�o�C�X����
	if ((device = create(hwnd, video::EDT_DIRECT3D9, this))) {
		TVPAddLog(L"DirectX9�ŏ�����");
	} else {
		if ((device = create(hwnd, video::EDT_DIRECT3D8, this))) {
			TVPAddLog(L"DirectX8�ŏ�����");
		} else {
			TVPThrowExceptionMessage(L"Irrlicht �f�o�C�X�̏������Ɏ��s���܂���");
		}
	}

	video::IVideoDriver* driver = device->getVideoDriver();
	dimension2d<s32> size = driver->getScreenSize();
	message_log("�f�o�C�X������̃X�N���[���T�C�Y:%d, %d", size.Width, size.Height);

	size = driver->getCurrentRenderTargetSize();
	message_log("�f�o�C�X�������RenderTarget��:%d, %d", size.Width, size.Height);

	
	//device->setWindowCaption(title.c_str());
	
	// �}�l�[�W���ɑ΂���e�N�X�`���̊��蓖��
	for (std::vector<iTVPLayerManager *>::iterator i = Managers.begin(); i != Managers.end(); i++) {
		allocInfo(*i);
	}

	// XXX �e�X�g�p
	init();
	
	// �쓮�J�n
	start();
}

/**
 * �E�C���h�E�̉���
 */
void
tTVPIrrlichtDrawDevice::detach()
{
	if (device) {
		stop();
		for (std::vector<iTVPLayerManager *>::iterator i = Managers.begin(); i != Managers.end(); i++) {
			freeInfo(*i);
		}
		device->drop();
		device = NULL;
	}
}

/**
 * ���C���}�l�[�W���̓o�^
 * @param manager ���C���}�l�[�W��
 */
void TJS_INTF_METHOD
tTVPIrrlichtDrawDevice::AddLayerManager(iTVPLayerManager * manager)
{
	allocInfo(manager);
	tTVPDrawDevice::AddLayerManager(manager);
}

/**
 * ���C���}�l�[�W���̍폜
 * @param manager ���C���}�l�[�W��
 */
void TJS_INTF_METHOD
tTVPIrrlichtDrawDevice::RemoveLayerManager(iTVPLayerManager * manager)
{
	freeInfo(manager);
	tTVPDrawDevice::RemoveLayerManager(manager);
}


/***
 * �E�C���h�E�̎w��
 * @param wnd �E�C���h�E�n���h��
 */
void TJS_INTF_METHOD
tTVPIrrlichtDrawDevice::SetTargetWindow(HWND wnd)
{
	detach();
	if (wnd != NULL) {
		attach(wnd);
	}
}


bool
tTVPIrrlichtDrawDevice::postEvent(SEvent &ev)
{
	if (device) {
		if (device->getGUIEnvironment()->postEventFromUser(ev) ||
			device->getSceneManager()->postEventFromUser(ev)) {
			return true;
		}
	}
	return false;
}

// -------------------------------------------------------------------------------------
// ���̓C�x���g�����p
// -------------------------------------------------------------------------------------

void TJS_INTF_METHOD
tTVPIrrlichtDrawDevice::OnMouseDown(tjs_int x, tjs_int y, tTVPMouseButton mb, tjs_uint32 flags)
{
	if (device) {
		SEvent ev;
		ev.EventType = EET_MOUSE_INPUT_EVENT;
		ev.MouseInput.X = x;
		ev.MouseInput.Y = y;
		ev.MouseInput.Wheel = 0;
		switch ((mb & 0xff)) {
		case mbLeft:
			ev.MouseInput.Event = EMIE_LMOUSE_PRESSED_DOWN;
			break;
		case mbRight:
			ev.MouseInput.Event = EMIE_RMOUSE_PRESSED_DOWN;
			break;
		case mbMiddle:
			ev.MouseInput.Event = EMIE_MMOUSE_PRESSED_DOWN;
			break;
		}
		if (postEvent(ev)) {
			return;
		}
	}
	// XXX ��ʃT�C�Y�ɉ������␳���K�v
	tTVPDrawDevice::OnMouseDown(x, y, mb, flags);
}

void TJS_INTF_METHOD
tTVPIrrlichtDrawDevice::OnMouseUp(tjs_int x, tjs_int y, tTVPMouseButton mb, tjs_uint32 flags)
{
	if (device) {
		SEvent ev;
		ev.EventType = EET_MOUSE_INPUT_EVENT;
		ev.MouseInput.X = x;
		ev.MouseInput.Y = y;
		ev.MouseInput.Wheel = 0;
		switch ((mb & 0xff)) {
		case mbLeft:
			ev.MouseInput.Event = EMIE_LMOUSE_LEFT_UP;
			break;
		case mbRight:
			ev.MouseInput.Event = EMIE_RMOUSE_LEFT_UP;
			break;
		case mbMiddle:
			ev.MouseInput.Event = EMIE_MMOUSE_LEFT_UP;
			break;
		}
		if (postEvent(ev)) {
			return;
		}
	}
	// XXX ��ʃT�C�Y�ɉ������␳���K�v
	tTVPDrawDevice::OnMouseUp(x, y, mb, flags);
}

void TJS_INTF_METHOD
tTVPIrrlichtDrawDevice::OnMouseMove(tjs_int x, tjs_int y, tjs_uint32 flags)
{
	if (device) {
		SEvent ev;
		ev.EventType = EET_MOUSE_INPUT_EVENT;
		ev.MouseInput.X = x;
		ev.MouseInput.Y = y;
		ev.MouseInput.Wheel = 0;
		ev.MouseInput.Event = EMIE_MOUSE_MOVED;
		if (postEvent(ev)) {
			return;
		}
	}
	// XXX ��ʃT�C�Y�ɉ������␳���K�v
	tTVPDrawDevice::OnMouseMove(x, y, flags);
}

void TJS_INTF_METHOD
tTVPIrrlichtDrawDevice::OnKeyDown(tjs_uint key, tjs_uint32 shift)
{
	tTVPDrawDevice::OnKeyDown(key, shift);
}

void TJS_INTF_METHOD
tTVPIrrlichtDrawDevice::OnKeyUp(tjs_uint key, tjs_uint32 shift)
{
	tTVPDrawDevice::OnKeyUp(key, shift);
}

void TJS_INTF_METHOD
tTVPIrrlichtDrawDevice::OnKeyPress(tjs_char key)
{
	tTVPDrawDevice::OnKeyPress(key);
}

void TJS_INTF_METHOD
tTVPIrrlichtDrawDevice::OnMouseWheel(tjs_uint32 shift, tjs_int delta, tjs_int x, tjs_int y)
{
	tTVPDrawDevice::OnMouseWheel(shift, delta, x, y);
}


// -------------------------------------------------------------------------------------
// �`�揈���p
// -------------------------------------------------------------------------------------

/**
 * �r�b�g�}�b�v�R�s�[�����J�n
 */
void TJS_INTF_METHOD
tTVPIrrlichtDrawDevice::StartBitmapCompletion(iTVPLayerManager * manager)
{
	LayerManagerInfo *info = (LayerManagerInfo*)manager->GetDrawDeviceData();
	if (info) {
		info->lock();
	}
}

/**
 * �r�b�g�}�b�v�R�s�[����
 */
void TJS_INTF_METHOD
tTVPIrrlichtDrawDevice::NotifyBitmapCompleted(iTVPLayerManager * manager,
	tjs_int x, tjs_int y, const void * bits, const BITMAPINFO * bitmapinfo,
	const tTVPRect &cliprect, tTVPLayerType type, tjs_int opacity)
{
	LayerManagerInfo *info = (LayerManagerInfo*)manager->GetDrawDeviceData();
	if (info) {
		info->copy(x, y, bits, bitmapinfo, cliprect, type, opacity);
	}
}

/**
 * �r�b�g�}�b�v�R�s�[�����I��
 */
void TJS_INTF_METHOD
tTVPIrrlichtDrawDevice::EndBitmapCompletion(iTVPLayerManager * manager)
{
	LayerManagerInfo *info = (LayerManagerInfo*)manager->GetDrawDeviceData();
	if (info) {
		info->unlock();
	}
}

//---------------------------------------------------------------------------

/**
 * �e�X�g�p����������
 */
void
tTVPIrrlichtDrawDevice::init()
{
	// GUI ���̃e�X�g
//	IGUIEnvironment* env = device->getGUIEnvironment();
//	env->addButton(rect<s32>(10,210,110,210 + 32), 0, 101, L"TEST BUTTON", L"Button Test");
//	env->addButton(rect<s32>(10,250,110,250 + 32), 0, 102, L"�Ă��Ƃڂ���", L"�{�^���̃e�X�g");
	
	/// �V�[���}�l�[�W���ł� irr �t�@�C�����[�h�̃e�X�g
	ISceneManager* smgr = device->getSceneManager();
	smgr->loadScene("data/sample/example.irr");
	smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
}
