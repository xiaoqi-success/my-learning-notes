#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>

#include "showwidget.h"

#include <QTextCharFormat>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

    void createActions();// 创建动作
    void createMenus();// 创建菜单
    void createToolBars();// 创建工具栏
    void loadFile(QString fileName);
    void mergeFormat(QTextCharFormat);

private:
    // 各项菜单栏
    QMenu *fileMenu;// 文件
    QMenu *zoomMenu;// 编辑
    QMenu *rotateMenu;// 旋转
    QMenu *mirrorMenu;// 镜像
    QImage img;
    QString fileName;
    ShowWidget *showWidget;
    // 文件菜单项
    QAction *openFileAction;
    QAction *newFileAction;
    QAction *printTextAction;
    QAction *printImageAction;
    QAction *exitAction;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *aboutAction;
    QAction *changeImgAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *rotate90Action;
    QAction *rotate180Action;
    QAction *rotate270Action;
    QAction *mirrorVerticalAction;
    QAction *mirrorHorizontalAction;
    QAction *undoAction;
    QAction *redoAction;
    // 工具栏
    QToolBar *fileTool;
    QToolBar *zoomTool;
    QToolBar *rotateTool;
    QToolBar *mirrorTool;
    QToolBar *doToolBar;

};
#endif // TEXTEDITOR_H
