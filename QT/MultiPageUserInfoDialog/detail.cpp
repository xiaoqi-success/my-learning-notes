#include "detail.h"

Detail::Detail(QWidget *parent) : QWidget(parent)
{
    QStringList countryList = {"美国","中国","英国","日本","韩国"};
    QStringList chinaProvenceList = {"安徽省","江苏省","江西省"};
    QStringList usaProvenceList = {"加利福尼亚州","德克萨斯州","纽约州"}; // 模拟美国数据
    QStringList ukProvenceList = {"英格兰","苏格兰","威尔士"};             // 模拟英国数据

    countryLabel = new QLabel("国家/地址:");
    provenceLabel = new QLabel("省份:");
    cityLabel = new QLabel("城市:");
    personalStateLabel = new QLabel("个人说明:");

    countryComboBox = new QComboBox();
    countryComboBox->addItems(countryList);
    countryComboBox->setCurrentIndex(1);// 默认是中国
    provenceComboBox = new QComboBox();
    // 初始化时，先让省份下拉框显示默认国家(中国)的省份
    provenceComboBox->addItems(chinaProvenceList);
    cityLineEdit = new QLineEdit();
    perStateTextEdit = new QTextEdit();

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(countryLabel,0,0);
    mainLayout->addWidget(countryComboBox,0,1);
    mainLayout->addWidget(provenceLabel,1,0);
    mainLayout->addWidget(provenceComboBox,1,1);
    mainLayout->addWidget(cityLabel,2,0);
    mainLayout->addWidget(cityLineEdit,2,1);
    mainLayout->addWidget(personalStateLabel,3,0);
    mainLayout->addWidget(perStateTextEdit,3,1);

    connect(countryComboBox,&QComboBox::currentTextChanged,this,&Detail::onCountryChanged);

}

void Detail::onCountryChanged(const QString &countryName)
{
    // 先清空旧的省份列表
    provenceComboBox->clear();
    // 根据国家名称匹配并添加新的省份
    if(countryName == "中国"){
        provenceComboBox->addItems({"安徽省", "江苏省", "江西省"});
    }else if (countryName == "美国") {
        provenceComboBox->addItems({"加利福尼亚州", "德克萨斯州", "纽约州"});
    } else if (countryName == "英国") {
        provenceComboBox->addItems({"英格兰", "苏格兰", "威尔士"});
    } else {
        // 其他国家，可以给个默认值或清空
        provenceComboBox->addItem("暂无数据");
    }
}
