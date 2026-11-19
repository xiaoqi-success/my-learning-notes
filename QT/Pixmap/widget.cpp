#include "widget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    resize(800,500);

    showLabel = new QLabel(this);
    // 关键！限制label最小宽高，不让图片把label撑爆
    showLabel->setMinimumSize(400,250);
    // 尺寸策略：不要跟随内容自动变大
    showLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    loadBtn = new QPushButton("加载图片",this);
    scaleBtn = new QPushButton("缩放图片",this);
    drawBtn = new QPushButton("绘制图片",this);
    saveBtn = new QPushButton("保存图片",this);
    copyBtn = new QPushButton("截取图片",this);

    gLayout = new QGridLayout();
    mainLayout = new QVBoxLayout(this);
    gLayout->addWidget(loadBtn,0,0);
    gLayout->addWidget(scaleBtn,0,1);
    gLayout->addWidget(drawBtn,1,0);
    gLayout->addWidget(saveBtn,1,1);
    gLayout->addWidget(copyBtn,2,0);

    mainLayout->addWidget(showLabel);
    mainLayout->addLayout(gLayout);

    connect(loadBtn,&QPushButton::clicked,this,&Widget::loadClicked);
    connect(scaleBtn,&QPushButton::clicked,this,&Widget::scaleClicked);
    connect(drawBtn,&QPushButton::clicked,this,&Widget::drawClicked);
    connect(saveBtn,&QPushButton::clicked,this,&Widget::saveClicked);
    connect(copyBtn,&QPushButton::clicked,this,&Widget::copyClicked);
}

Widget::~Widget()
{
}

// 加载本地图片
void Widget::loadClicked()
{
    // 先打开图片
    QString filePath = QFileDialog::getOpenFileName(this,"选择图片","D:/Image","图片(*.png;*.jpg;*.bmp)");
    if(filePath.isEmpty()){
        return;
    }
    // 加载图片
    m_pix.load(filePath);
    if(m_pix.isNull()){
        QMessageBox::warning(this,"错误","图片加载失败");
        return;
    }
    showLabel->setPixmap(m_pix);
    showLabel->setScaledContents(false);// 禁用掉，自己实现缩放，不开启label自动拉伸
}

// 缩放图片
void Widget::scaleClicked()
{
    if(m_pix.isNull()){
        return;
    }
    QPixmap scalePix = m_pix.scaled(showLabel->width(),showLabel->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    showLabel->setPixmap(scalePix);
}

// 在空白QPixmap上绘图，然后显示
void Widget::drawClicked()
{
    // 准备一张400*300大小的画布
    QPixmap drawPix(400,300);
    drawPix.fill(Qt::lightGray);
    // 创建绘图对象，绑定到这张pixmap画布上（离屏绘图：画在内存图片上，不是直接画控件）
    QPainter p(&drawPix);
    // 设置画笔：蓝色、线宽2像素，后面画图形都用这个画笔
    p.setPen(QPen(Qt::blue,2));
    // 画椭圆：起点x = 50，y = 50，外接矩形宽100，高100 → 宽高相等就是正圆
    p.drawEllipse(50,50,100,100);
    // 绘制文字：文字左下角坐标(100,200)，内容"QPixmap 离屏绘图"
    // 注意：drawText这个重载，坐标是文字左下角，不是左上角！
    p.drawText(100,200,"QPixmap离屏绘图");
    // 结束绘图，释放painter资源，必须写end()；超出作用域自动析构也可以，但显式写更规范
    p.end();
    // 把画好的图片赋值给我们保存原图的成员变量m_pix
    m_pix = drawPix;
    // 把绘制完成的图片放到label上显示出来
    showLabel->setPixmap(m_pix);
}

// 保存图片
void Widget::saveClicked()
{
    if(m_pix.isNull()){
        return;
    }
    QString savePath = QFileDialog::getSaveFileName(this,"保存图片","C:/Users/Administrator/OneDrive/桌面","PNG(*.png)");
    if(savePath.isEmpty()){
        return;
    }
    bool ok = m_pix.save(savePath,"png");
    if(ok){
        QMessageBox::information(this,"提示","保存成功");
    }else{
        QMessageBox::warning(this,"提示","保存失败");
    }
}

// 裁剪图片
void Widget::copyClicked()
{
    if(m_pix.isNull()){
        return;
    }
    // copy(x,y,width,height)
    // x,y：裁剪区域左上角在原图上的坐标
    // 后面两个：裁剪区域的宽、高
    QPixmap copyPix = m_pix.copy(20,20,120,120);
//    m_pix = copyPix; // 把裁剪后的图覆盖原图，后续操作都基于裁好的图
    showLabel->setPixmap(copyPix);
}

