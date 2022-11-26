#include "GUI.h"
#include<iostream>

GUI::GUI()
{
	// Initialize user interface parameters
	InterfaceMode = MODE_DRAW;

	width = 1200;
	height = 600;
	wx = 5;
	wy = 5;

	StatusBarHeight = 50;
	ToolBarHeight = 50;
	MenuIconWidth = 80;

	DrawColor = BLUE;		  // default Drawing color
	FillColor = GREEN;		  // default Filling color
	MsgColor = BLACK;		  // Messages color
	BkGrndColor = WHITE;	  // Background color
	HighlightColor = MAGENTA; // This color should NOT be used to draw shapes. use if for highlight only
	StatusBarColor = LIGHTSEAGREEN;
	PenWidth = 3; // default width of the shapes frames

	// Create the output window
	pWind = CreateWind(width, height, wx, wy);
	// Change the title
	pWind->ChangeTitle("- - - - - - - - - - PAINT ^ ^ PLAY - - - - - - - - - -");

	CreateDrawToolBar();
	CreateStatusBar();
}

//======================================================================================//
//								Input Functions										//
//======================================================================================//
void GUI::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y); // Wait for mouse click
}

void GUI::GetKeyClicked(char &Key) const
{
	pWind->WaitKeyPress(Key); // Get the keyboard button clicked
}

string GUI::GetSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE) // ESCAPE key is pressed
			return "";		 // returns nothing as user has cancelled label
		if (Key == 13)		 // ENTER key is pressed
			return Label;
		if (Key == 8) // BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		PrintMessage(Label);
	}
}

// This function reads the position where the user clicks to determine the desired operation
operationType GUI::GetUseroperation() const
{
	int x, y;
	pWind->WaitMouseClick(x, y); // Get the coordinates of the user click

	if (InterfaceMode == MODE_DRAW) // GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < ToolBarHeight)
		{
			// Check whick Menu icon was clicked
			//==> This assumes that menu icons are lined up horizontally <==
			int ClickedIconOrder = (x / MenuIconWidth);
			// Divide x coord of the point clicked by the menu icon width (int division)
			// if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

			switch (ClickedIconOrder)
			{
			case ICON_RECT: return DRAW_RECT;
			case ICON_CIRC: return DRAW_CIRC;
			case ICON_TRIANGLE: return DRAW_TRI;
			case ICON_OVAL: return DRAW_OVAL;
			case ICON_REGULAR_POLYGON: return DRAW_REGULAR_POLYGON;
      case ICON_IRR_POLYGON: return DRAW_IRR_POLYGON;
			case ICON_LINE: return DRAW_LINE;
			case ICON_EXIT: return EXIT;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= ToolBarHeight && y < height - StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else // GUI is in PLAY mode
	{
		/// TODO:
		// perform checks similar to Draw mode checks above
		// and return the correspoding operation
		return TO_PLAY; // just for now. This should be updated
	}
}
////////////////////////////////////////////////////

//======================================================================================//
//								Output Functions										//
//======================================================================================//

window *GUI::CreateWind(int w, int h, int x, int y) const
{
	window *pW = new window(w, h, x, y);
	pW->SetBrush(BkGrndColor);
	pW->SetPen(BkGrndColor, 1);
	pW->DrawRectangle(0, ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	// Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar()
{
	InterfaceMode = MODE_DRAW;

	// You can draw the tool bar icons in any way you want.
	// Below is one possible way

	// First prepare List of images for each menu icon
	// To control the order of these images in the menu,
	// reoder them in UI_Info.h ==> enum DrawMenuIcon
	string MenuIconImages[DRAW_ICON_COUNT];
	MenuIconImages[ICON_RECT] = "images\\MenuIcons\\Menu_Rect.jpg";
	MenuIconImages[ICON_CIRC] = "images\\MenuIcons\\Menu_Circ.jpg";
	MenuIconImages[ICON_TRIANGLE] = "images\\MenuIcons\\Menu_Triangle.jpg";
	MenuIconImages[ICON_OVAL] = "images\\MenuIcons\\Menu_Oval.jpg";

	MenuIconImages[ICON_IRR_POLYGON] = "images\\MenuIcons\\Menu_IrrPolygon.jpg";
	MenuIconImages[ICON_REGULAR_POLYGON] = "images\\MenuIcons\\Menu_RegShape.jpg";
	MenuIconImages[ICON_LINE] = "images\\MenuIcons\\Menu_Line.jpg";

	MenuIconImages[ICON_EXIT] = "images\\MenuIcons\\Menu_Exit.jpg";

	// TODO: Prepare images for each menu icon and add it to the list

	// Draw menu icon one image at a time
	for (int i = 0; i < DRAW_ICON_COUNT; i++)
		pWind->DrawImage(MenuIconImages[i], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight);

	// Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar()
{
	InterfaceMode = MODE_PLAY;
	/// TODO: write code to create Play mode menu
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const // Prints a message on status bar
{
	ClearStatusBar(); // First clear the status bar

	pWind->SetPen(MsgColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, height - (int)(0.75 * StatusBarHeight), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const // get current drwawing color
{
	return DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const // get current filling color
{
	return FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int GUI::getCrntPenWidth() const // get current pen width
{
	return PenWidth;
}

//======================================================================================//
//								shapes Drawing Functions								//
//======================================================================================//

void GUI::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const
{
	color DrawingClr;
	if (RectGfxInfo.isSelected)		 // shape is selected
		DrawingClr = HighlightColor; // shape should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth); // Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
}

void GUI::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriaGfxInfo) const
{
	color DrawingClr;
	if (TriaGfxInfo.isSelected)		 // shape is selected
		DrawingClr = HighlightColor; // shape should be drawn highlighted
	else
		DrawingClr = TriaGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, TriaGfxInfo.BorderWdth); // Set Drawing color & width

	drawstyle style;
	if (TriaGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriaGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}

void GUI::DrawCircle(Point P1, Point P2, GfxInfo CirclGfxInfo) const
{
	color DrawingClr;
	if (CirclGfxInfo.isSelected)	 // shape is selected
		DrawingClr = HighlightColor; // shape should be drawn highlighted
	else
		DrawingClr = CirclGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, CirclGfxInfo.BorderWdth); // Set Drawing color & width

	drawstyle style;
	if (CirclGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CirclGfxInfo.FillClr);
	}
	else
		style = FRAME;

	int radius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));

	pWind->DrawCircle(P1.x, P1.y, radius, style);
}

void GUI::DrawOval(Point P1, Point P2, GfxInfo OvalGfxInfo) const
{
	color DrawingClr;
	if (OvalGfxInfo.isSelected)		 // shape is selected
		DrawingClr = HighlightColor; // shape should be drawn highlighted
	else
		DrawingClr = OvalGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, OvalGfxInfo.BorderWdth); // Set Drawing color & width

	drawstyle style;
	if (OvalGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(OvalGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawEllipse(P1.x, P1.y, P2.x, P2.y, style);
}

void GUI::DrawRegularPolygon(Point center, double numOfVertices, double radius, GfxInfo RegularPolygonGfxInfo) const
{
	color DrawingClr;
	if (RegularPolygonGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = RegularPolygonGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RegularPolygonGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RegularPolygonGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RegularPolygonGfxInfo.FillClr);
	}
	else
		style = FRAME;


		std::vector<int> xPointsV;
		std::vector<int> yPointsV;

		const double PI = 3.141592653589;			//Defining constant PI
		double angle = (2 * PI) / numOfVertices;	//Defining the angle between two vertices

		for (int i = 0; i < int(numOfVertices); i++)
		{
			int x = center.x + radius * sin(i * angle);
			int y = center.y + radius * cos(i * angle);

			xPointsV.push_back(x);
			yPointsV.push_back(y);
		}

		int* xPoints = &xPointsV[0];
		int* yPoints = &yPointsV[0];

		pWind->DrawPolygon(xPoints, yPoints, int(numOfVertices), style);

}

void GUI::DrawLine(Point P1, Point P2, GfxInfo LineGfcInfo) const
{
	color DrawingClr;
	if (LineGfcInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = LineGfcInfo.DrawClr;

	pWind->SetPen(DrawingClr, LineGfcInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (LineGfcInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(LineGfcInfo.FillClr);
	}
	else
		style = FRAME;

  pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);
  }
  
void GUI::DrawIrrPolygon(vector<Point> allPoints, int verticies, GfxInfo IrrPolGfxInfo) const
{
	color DrawingClr;
	if (IrrPolGfxInfo.isSelected)	 // shape is selected
		DrawingClr = HighlightColor; // shape should be drawn highlighted
	else
		DrawingClr = IrrPolGfxInfo.DrawClr;
	pWind->SetPen(DrawingClr, IrrPolGfxInfo.BorderWdth); // Set Drawing color & width

	drawstyle style;
	if (IrrPolGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(IrrPolGfxInfo.FillClr);
	}
	else
		style = FRAME;
	vector<int> xPointsV;
	vector<int> yPointsV;
	for (int i = 0; i < verticies; i++)
	{
		xPointsV.push_back(allPoints[i].x);
		yPointsV.push_back(allPoints[i].y);
	}
	int *xPoints = &xPointsV[0];
	int *yPoints = &yPointsV[0];
	pWind->DrawPolygon(xPoints, yPoints, verticies, style);
}

GUI::~GUI()
{
	delete pWind;
}
