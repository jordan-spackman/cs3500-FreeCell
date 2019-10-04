#pragma once
#include <vector>
class Cell
{
public:
	Cell(int left, int top, int right, int bottom);

	virtual void Draw(CDC& dc);

	void AddCard(int index);
	void RemoveCard();

	int Cell::CardCount();
	int Cell::GetTopCard();


	virtual bool CanRemoveCard();
	virtual bool CanAcceptCard(int index);

	bool IsClicked(int x, int y); //convert to World Coordinates
	void SetSelected(bool selected);

	std::vector<int> mCards;

	//getTopCard will need to be added.

protected:
	int mLeft, mTop, mRight, mBottom;
	bool mSelected = false;
	int mLastCard = -1;
};

class StartCell : public Cell {
public:
	StartCell(int left, int top, int right, int bottom);
	//overide draw so that it stacks
	virtual void Draw(CDC& dc);
	virtual bool CanRemovedCard();
	virtual bool CanAcceptCard(int index);
private:
	//int mCardHeight;
};

class FreeCell : public Cell {
public:
	FreeCell(int left, int top, int right, int bottom);
	virtual bool CanRemovedCard();
	virtual bool CanAcceptCard(int index);
};

class EndCell : public Cell {
public:
	EndCell(int left, int top, int right, int bottom);
	virtual bool CanRemoveCard();
	virtual bool CanAcceptCard(int index);

};
