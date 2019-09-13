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

	bool IsClicked(double x, double y); //convert to World Coordinates
	void SetSelected(bool selected);

	//getTopCard will need to be added. 

private:
	std::vector<int> mCards;
	double mLeft, mTop, mRight, mBottom;
	bool mSelected;
};

class StartCell : public Cell {
public:
	StartCell(double left, double top, double right, double bottom, double cardHeight);
	//overide draw so that it stacks
	virtual void Draw(CDC& dc, int width, int height,  CImage images[])
private:
	double mCardHeight;
};

class FreeCell : public Cell {
public:
	FreeCell(double left, double top, double right, double bottom);
};

class EndCell : public Cell {
public:
	EndCell(double left, double top, double right, double bottom);
	virtual bool CanRemoveCard();
};
