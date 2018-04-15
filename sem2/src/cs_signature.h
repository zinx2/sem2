#pragma once
#include "cs_qheader.h"
#include "cs_model.h"
#define SIZE_PEN 3
#define WIDTH_SIGN_ZONE 480
#define HEIGHT_SIGN_ZONE 200

//class Model;
//class SignZone;
//class DialogSign : public QDialog
//{
//	Q_OBJECT
//
//public:
//	explicit DialogSign(QWidget *parent = 0);
//
//	public slots:
//	void off();
//	void save();
//
//signals:
//	void saved();
//
//private:
//	Model* m;
//	SignZone* signZone;
//};

class PaintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit PaintScene(int width, int height, QObject *parent = 0) : QGraphicsScene(parent)
	{
		setSceneRect(QRectF(0, 0, width, height));
	}


private:
    QPointF     previousPoint;
    void mousePressEvent(QGraphicsSceneMouseEvent * event)
	{
		// When you press the mouse button, draw the ellipse

		addEllipse(event->scenePos().x() - 5,
			event->scenePos().y() - 5,
			SIZE_PEN,
			SIZE_PEN,
			QPen(Qt::NoPen),
			QBrush(Qt::black));
		// Save the coordinates of the point of pressing
		previousPoint = event->scenePos();
	}
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
	{
		// We draw the line with the previous coordinates
		addLine(previousPoint.x(),
			previousPoint.y(),
			event->scenePos().x(),
			event->scenePos().y(),
			QPen(Qt::black, SIZE_PEN, Qt::SolidLine, Qt::RoundCap));
		// Update on the previous coordinate data
		previousPoint = event->scenePos();
	}

};

class Signature : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Signature(QWidget *parent = 0) : QGraphicsView(parent)
	{

		width = parent->width();// -horizontalScrollBar()->height();
		height = parent->height();// -verticalScrollBar()->width();
		setFixedWidth(width); setFixedHeight(height);
		setScene(new PaintScene(width, height, this));
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setStyleSheet("background: white; border: 1px solid #7a7a7a");
		setContentsMargins(0, 0, 0, 0);
	}
    bool toImage()
	{
		QString fileName = QDir::currentPath() + "/tmp.jpg";
		QPixmap pixMap = QPixmap::grabWidget(this);
		bool result = pixMap.save(fileName);
		if(!result)
			Model::instance()->request(false, Notificator::ErrorNoSaveFile);
		return result;
	}

    void init()
	{
		setScene(new PaintScene(width, height, this));
	}
private:
    int width;
    int height;
};
