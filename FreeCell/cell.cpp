#include "pch.h"
#include "cell.h"
#include "WindowsCards.h"
Cell::Cell(int left, int top, int right, int bottom)
{
	mLeft = left;
	mTop = top;
	mRight = right;
	mBottom = bottom;
}
void Cell::Draw(CDC& dc)
{
	CBrush cellBackgroundColor(RGB(128, 255, 128));
	dc.SelectObject(cellBackgroundColor);
	dc.Rectangle(mLeft, mTop, mRight, mBottom);

	if (mCards.size() > 0)
	{
		DrawCard(dc, mLeft+2, mTop+2, mCards[mCards.size()-1]);
	}
}

void Cell::AddCard(int index)
{
	mCards.push_back(index);
}

void Cell::RemoveCard()
{
	mCards.pop_back();
}

bool Cell::CanRemoveCard()
{
	return mCards.size()>0;
	//will return True if bigger than 0, else false
}
bool Cell::CanAcceptCard(int index)
{
	//rules are different for all three child classes so it will need to be overwritted.
	return true;
}

bool Cell::IsClicked(int x, int y)
{
	return (x >= mLeft && x <= mRight && y >= mTop && y <= mBottom);
}
void Cell::SetSelected(bool selected)
{
	mSelected = selected;
}

StartCell::EndCell(double left, double top, double right, double bottom)
	: Cell(left, top, right, bottom)
{

}

FreeCell::EndCell(double left, double top, double right, double bottom)
	: Cell(left, top, right, bottom)
{

}


EndCell::EndCell(double left, double top, double right, double bottom)
	: Cell(left, top, right, bottom)
{

}

//overides the CanRemoveCard for EndCell child class
bool EndCell::CanRemoveCard() {
	return false;
}
