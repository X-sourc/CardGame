#include "UndoManager.h"

UndoManager* UndoManager::_instance = nullptr;

UndoManager* UndoManager::getInstance()
{
    if (!_instance)
    {
        _instance = new UndoManager();
    }
    return _instance;
}

void UndoManager::destroyInstance()
{
    if (!_instance) return;

    // Çå¿ÕÕ»
    while (!_instance->_undoStack.empty())
    {
        UndoModel* record = _instance->_undoStack.top();
        delete record;
        _instance->_undoStack.pop();
    }

    delete _instance;
    _instance = nullptr;
}

UndoManager::UndoManager()
{
}

UndoManager::~UndoManager()
{
}

void UndoManager::addUndoRecord(UndoModel* record)
{
    if (record)
    {
        _undoStack.push(record);
    }
}

UndoModel* UndoManager::popUndoRecord()
{
    if (_undoStack.empty())
    {
        return nullptr;
    }

    UndoModel* record = _undoStack.top();
    _undoStack.pop();
    return record;
}

bool UndoManager::isEmpty()
{
    return _undoStack.empty();
}

