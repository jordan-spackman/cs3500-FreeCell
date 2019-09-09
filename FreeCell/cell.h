#pragma once
#include <vector>
class Cell
{
public:
	Cell(int left, int top, int right, int bottom);
	void Draw(CDC& dc);

	void AddCard(int index);
	void RemoveCard();

	bool CanRemoveCard();
	bool CanAcceptCard(int index);

	bool IsClicked(int x, int y);
	void SetSelected(bool selected);

private:
	std::vector<int> mCards;
	int mLeft, mTop, mRight, mBottom;
	bool mSelected;
};