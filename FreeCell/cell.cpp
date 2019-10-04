#include "pch.h"
#include "cell.h"
#include "WindowsCards.h"
#include "WindowsCards.h"
#include <windows.h>
#include "FreeCellDlg.h"

Cell::Cell(int left, int top, int right, int bottom)
{
	mLeft = left;
	mTop = top;
	mRight = right;
	mBottom = bottom;
}
void Cell::Draw(CDC& dc)
{
	CBrush cellBackgroundColor(RGB(128, 128, 128));
	dc.SelectObject(cellBackgroundColor);
	dc.Rectangle(mLeft, mTop, mRight, mBottom);

	if (mCards.size() > 0)
	{
	
		DrawCard(dc, mLeft + 2, mTop + 2, mCards[mCards.size() - 1]);
		
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

int Cell::CardCount()
{
	return mCards.size();
}

int Cell::GetTopCard()
{
	return mCards[mCards.size() - 1];
}


//will return True if bigger than 0, else false
bool Cell::CanRemoveCard() {
	if (mCards.size() > 0) {
		return true;
	}
	else
	{
		MessageBox(NULL, L"Error: Cannot perform action.", L"MessageBox caption", MB_OK);
		return false;
	}

}
bool Cell::CanAcceptCard(int index)
{
	return TRUE;
}


bool Cell::IsClicked(int x, int y)
{
	return (x >= mLeft && x <= mRight && y >= mTop && y <= mBottom);
}
void Cell::SetSelected(bool selected) 
{
	mSelected = selected;
};

StartCell::StartCell(int left, int top, int right, int bottom)
	: Cell(left, top, right, bottom)
{

}

void StartCell::Draw(CDC& dc)
{
	CBrush cellBackgroundColor(RGB(128, 128, 128));
	dc.SelectObject(cellBackgroundColor);
	dc.Rectangle(mLeft, mTop, mRight, mBottom);

	if (mCards.size() > 0)
	{
		for (int i = 0; i < mCards.size(); i++) {
			DrawCard(dc, mLeft + 2, mTop + 2 + i * 25, mCards[i], mSelected);
		}
	}
}

bool StartCell::CanRemovedCard() {
	return TRUE;
}
bool StartCell::CanAcceptCard(int index) {
	if (mCards.size() == 0) {
		return TRUE;
	}
	int firstRank = index / 4;
	int firstSuit = index % 4;
	bool firstRed = firstSuit == 1 || firstSuit == 2;

	int secondRank = this->GetTopCard() / 4;
	int secondSuit = this->GetTopCard() % 4;
	bool secondRed = secondSuit == 1 || secondSuit == 2;


	if (firstRed != secondRed && firstRank == secondRank - 1) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}



FreeCell::FreeCell(int left, int top, int right, int bottom)
	: Cell(left, top, right, bottom)
{

}

bool FreeCell::CanRemovedCard()
{
	return TRUE;
}

bool FreeCell::CanAcceptCard(int index)
{

	if (mCards.size() == 0) {
		return TRUE;
	}
	else if (mCards.size() > 1) {
		int test = this->GetTopCard();
		if (test < index) {
			return TRUE;
		}
	}
	else {
		return FALSE;
	}
}

EndCell::EndCell(int left, int top, int right, int bottom)
	: Cell(left, top, right, bottom)
{

}

//overides the CanRemoveCard for EndCell child class
bool EndCell::CanRemoveCard() {
	return FALSE;
}

bool EndCell::CanAcceptCard(int index) {
	if (this->mCards.size() == 0) {
		if (index == 0 || index == 1 || index == 2 || index == 3) {
			return TRUE;
		}
		return FALSE;
	}
	// works till this point
	else if (this->mCards.size() > 0) {
		int firstRank = index / 4;
		int firstSuit = index % 4;
		bool firstRed = firstSuit == 1 || firstSuit == 2;
		int secondRank = this->GetTopCard() / 4;
		int secondSuit = this->GetTopCard() % 4;
		bool secondRed = secondSuit == 1 || secondSuit == 2;
		if (firstRed != secondRed && firstRank == secondRank - 1) {
			return TRUE;
		}
		return FALSE;
	}
}
