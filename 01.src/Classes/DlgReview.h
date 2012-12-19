#ifndef _DialogReview_H_
#define _DialogReview_H_

class DialogReview : public CCLayerColor
{
    CCLayer* _layerBase;

	bool _init(CCNode* parent);
	void _menuCallback(CCMenuItem* sender);
    void _closeDialog();
    void _closeDialogWithReview();

public:
    DialogReview();
    ~DialogReview();
    
    static DialogReview* create(CCNode* parent);

    void onEnter();
    void onExit();
	bool ccTouchBegan(CCTouch* touch, CCEvent* event);
};

#endif