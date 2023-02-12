
// OpenGlView.cpp: реализация класса COpenGlView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "OpenGl.h"
#endif

#include "OpenGlDoc.h"
#include "OpenGlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGlView

IMPLEMENT_DYNCREATE(COpenGlView, CView)

BEGIN_MESSAGE_MAP(COpenGlView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение COpenGlView

COpenGlView::COpenGlView() noexcept
{
	// TODO: добавьте код создания

}

COpenGlView::~COpenGlView()
{
}

BOOL COpenGlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
	//cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

// Рисование COpenGlView

void COpenGlView::OnDraw(CDC* /*pDC*/)
{
	COpenGlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
	opengl.Render(pDoc);
}


// Печать COpenGlView

BOOL COpenGlView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void COpenGlView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void COpenGlView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика COpenGlView

#ifdef _DEBUG
void COpenGlView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGlDoc* COpenGlView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGlDoc)));
	return (COpenGlDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений COpenGlView


void COpenGlView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: добавьте специализированный код или вызов базового класса
	
	opengl.SetupPixelFormat(::GetDC(GetSafeHwnd()));
	opengl.Init();
}


void COpenGlView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: добавьте свой код обработчика сообщений
	if (cx == 0)
	{
		cx = 1;
	}
	opengl.Reshape(cx, cy);
}


void COpenGlView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	

	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL COpenGlView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	COpenGlDoc* pDoc = GetDocument();
	
	float  del = (abs(zDelta) / (100.f * zDelta));
	pDoc->m_Scale += del;
	if (pDoc->m_Scale <= 0)
	{
		pDoc->m_Scale -= del;
	}
	Invalidate(FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}



void COpenGlView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	COpenGlDoc* pDoc = GetDocument();

	CPoint deltaLast;

	if (start) {

		deltaLast = -lastPoint + point;

		if (flagRotation) {
			pDoc->Rotation.x -= (-lastPoint.y + point.y);
			pDoc->Rotation.z += (-lastPoint.x + point.x);
		}
		if (flagTrans) {
			pDoc->trans.x += deltaLast.x / 210.0;
			pDoc->trans.y -= deltaLast.y / 100.0;
		}

	}
	lastPoint = point;

	Invalidate(FALSE);
	CView::OnMouseMove(nFlags, point);
}


void COpenGlView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	start = true;
	flagTrans = true;
	CView::OnLButtonDown(nFlags, point);
}


void COpenGlView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	start = false;
	flagTrans = false;
	CView::OnLButtonUp(nFlags, point);
}


void COpenGlView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	start = true;
	flagRotation = true;
	CView::OnMButtonDown(nFlags, point);
}


void COpenGlView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	start = false;
	flagRotation = false;
	CView::OnMButtonUp(nFlags, point);
}
