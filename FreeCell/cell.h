#pragma once
#include <vector>
class Cell
{
public:
	Cell(int left, int top, int right, int bottom);

	virtual void Draw(CDC& dc, int width, int height, CImage images[]);

	void AddCard(int index);
	void RemoveCard();

	virtual bool CanRemoveCard();
	virtual bool CanAcceptCard(int index);

	bool IsClicked(int x, int y); //convert to World Coordinates
	void SetSelected(bool selected);

	//getTopCard will need to be added. 

private:
	std::vector<int> mCards;
	int mLeft, mTop, mRight, mBottom;
	bool mSelected;
};

class StartCell : public Cell {
public:
	StartCell(int left, int top, int right, int bottom, int cardHeight);
	//overide draw so that it stacks
	virtual void Draw(CDC& dc, int width, int height, CImage images[]);
private:
	int mCardHeight;
};

class FreeCell : public Cell {
public:
	FreeCell(int left, int top, int right, int bottom);
};

class EndCell : public Cell {
public:
	EndCell(int left, int top, int right, int bottom);
	virtual bool CanRemoveCard();
};
