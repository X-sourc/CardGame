#ifndef _UNDO_MANAGER_H_
#define _UNDO_MANAGER_H_

#include "cocos2d.h"
#include "models/UndoModel.h"
#include <stack>

class UndoManager
{
public:
    static UndoManager* getInstance();
    static void destroyInstance();
    void addUndoRecord(UndoModel* record);
    UndoModel* popUndoRecord();
    bool isEmpty();

private:
    UndoManager();
    ~UndoManager();
    static UndoManager* _instance;
    std::stack<UndoModel*> _undoStack;
};

#endif