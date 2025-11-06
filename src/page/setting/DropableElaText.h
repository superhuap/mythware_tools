#ifndef DROPABLEELATEXT_H
#define DROPABLEELATEXT_H

#include <ElaText.h>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfo>
#include <QPainter>
#include <QPen>

class DropableElaText : public ElaText {
Q_OBJECT
public:
    explicit DropableElaText(QWidget* parent = nullptr) : ElaText(parent), _dragging(false), _validDrag(false) {
        setAcceptDrops(true);
        setMinimumHeight(20);  // 设置最小高度确保可拖拽区域
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);  // 设置尺寸策略
    }

signals:
    void fileDropped(const QString& filePath);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override {
        if (event->mimeData()->hasUrls()) {
            QList<QUrl> urls = event->mimeData()->urls();
            if (!urls.isEmpty()) {
                QString filePath = urls.first().toLocalFile();
                QFileInfo fileInfo(filePath);
                
                // 检查文件是否存在且是文件
                if (fileInfo.exists() && fileInfo.isFile()) {
                    _dragging = true;
                    // 检查是否是xml文件
                    if (fileInfo.suffix().toLower() == "xml") {
                        _validDrag = true;
                    } else {
                        _validDrag = false; // 不是xml文件
                    }
                    update(); // 触发重绘
                    event->acceptProposedAction();
                    return;
                }
            }
        }
        event->ignore();
    }

    void dragLeaveEvent(QDragLeaveEvent* event) override {
        _dragging = false;
        _validDrag = false;
        update(); // 触发重绘
        ElaText::dragLeaveEvent(event);
    }

    void dropEvent(QDropEvent* event) override {
        _dragging = false;
        _validDrag = false;
        update(); // 触发重绘
        
        if (event->mimeData()->hasUrls()) {
            QList<QUrl> urls = event->mimeData()->urls();
            if (!urls.isEmpty()) {
                QString filePath = urls.first().toLocalFile();
                QFileInfo fileInfo(filePath);
                
                // 检查文件是否是xml文件
                if (fileInfo.exists() && fileInfo.isFile() && 
                    fileInfo.suffix().toLower() == "xml") {
                    emit fileDropped(filePath);
                    event->acceptProposedAction();
                    return;
                }
            }
        }
        event->ignore();
    }
    
    // 重写绘制事件以添加边框效果
    void paintEvent(QPaintEvent* event) override {
        ElaText::paintEvent(event);
        
        if (_dragging) {
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);
            
            QPen pen;
            if (_validDrag) {
                pen.setColor(Qt::green); // 有效拖拽（XML文件）显示绿色
            } else {
                pen.setColor(Qt::red); // 无效拖拽（非XML文件）显示红色
            }
            pen.setWidth(2);
            painter.setPen(pen);
            painter.drawRoundedRect(1, 1, width() - 2, height() - 2, 4, 4);
        }
    }
    
    // 重写尺寸提示方法确保最小尺寸
    QSize sizeHint() const override {
        QSize size = ElaText::sizeHint();
        size.setHeight(qMax(size.height(), 20));
        return size;
    }
    
    QSize minimumSizeHint() const override {
        QSize size = ElaText::minimumSizeHint();
        size.setHeight(qMax(size.height(), 20));
        return size;
    }

private:
    bool _dragging;   // 标记是否正在拖拽
    bool _validDrag;  // 标记拖拽的文件是否为有效的XML文件
};

#endif // DROPABLEELATEXT_H