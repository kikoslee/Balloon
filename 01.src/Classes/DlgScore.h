#ifndef _DialogScore_H_
#define _DialogScore_H_

class DialogScore : public CCLayerColor
{
    CCLayer* _layerBase;
    bool _isClear;
    std::string _shareMsg;

	bool _initWithCount(int count, CCNode* parent);
	void _menuCallback(CCMenuItem* sender);
    void _closeDialog();
    void _checkReview();
    void _showDialogReview();

public:
    DialogScore();
    ~DialogScore();
    
    static DialogScore* create(int count, CCNode* parent);

    void onEnter();
    void onExit();
	bool ccTouchBegan(CCTouch* touch, CCEvent* event);
};

#endif