#ifndef TASCHENRECHNER_H
#define TASCHENRECHNER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Taschenrechner; }
QT_END_NAMESPACE

class Taschenrechner : public QMainWindow
{
	Q_OBJECT

public:
	//Konstruktor
	Taschenrechner(QWidget *parent = nullptr);
	// Destruktor
	~Taschenrechner();


private slots:
	void digit_pressed();				// Slot für Ziffern-Buttons
	void binary_operation_pressed();	// Slot für Operation (+, -, *, /)
	void equals_pressed();				// Slot für den Gleichheits-Button (=)
	void clear_pressed();				// Slot für den Löschen-Button

private:
	Ui::Taschenrechner *ui;

	double firstNumber;					// Speichert die erste Zahl
	double secondNumber;				// Speichert die zweite Zahl
	bool userIsTypingSecondNumber;		// Flag, ob der Benutzer die zweite Zahl eingibt
	QString currentOperation;			// Speichert die aktuelle Operation (+, -, *, /)
};









#endif // TASCHENRECHNER_H