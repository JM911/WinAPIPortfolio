#pragma once

#define SAFE_DELETE(p)			if(p) { delete p; p = NULL; }
#define SAFE_DELETE_ARRAY(p)	if(p) { delete[] p; p = NULL; }
#define SAFE_RELEASE(p)			if(p) { p->Release(); p = NULL; }

#define DECLARE_SINGLE(Type)\
	private:\
		static Type*	m_pInst;\
	public:\
		static Type*	GetInst()\
		{\
			if(!m_pInst)\
				m_pInst = new Type;\
			return m_pInst;\
		}\
		static void DestroyInst()\
		{\
			SAFE_DELETE(m_pInst);\
		}

#define DEFINITION_SINGLE(Type)	Type* Type::m_pInst = NULL;

#define GET_SINGLE(Type)		Type::GetInst()
#define	DESTROY_SINGLE(Type)	Type::DestroyInst()

#define GETRESOLUTION	Core::GetInst()->GetResolution()
#define GETWORLDRES		Core::GetInst()->GetWorldResolution()
#define WINDOWHANDLE	Core::GetInst()->GetWindowHandle()
#define WINDOWINSTANCE	Core::GetInst()->GetWindowInstance()

#define KEYDOWN(key)	CInput::GetInst()->KeyDown(key)
#define KEYPRESS(key)	CInput::GetInst()->KeyPress(key)
#define KEYUP(key)		CInput::GetInst()->KeyUp(key)