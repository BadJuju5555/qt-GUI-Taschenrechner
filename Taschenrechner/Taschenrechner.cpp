#include "Taschenrechner.h"
#include "ui_Taschenrechner.h"
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>

Taschenrechner::Taschenrechner(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::Taschenrechner)
	, firstNumber(0.0)
	, secondNumber(0.0)
	, userIsTypingSecondNumber(false)
{
	ui->setupUi(this);

	// Verbindung der Ziffern-Buttons mit dem Slot digit_pressed()
	QList<QPushButton*> digitButtons = this->findChildren<QPushButton*>();

	foreach(QPushButton* button, digitButtons)
	{
		bool ok;
		int digit = button->text().toInt(&ok);


		if (ok && digit >= 0 && digit <= 9)
		{
			connect(button, &QPushButton::clicked, this, &Taschenrechner::digit_pressed);
		}
	}

	// Verbindung der Operations-Buttons mit dem slot binary_operation_pressed
	connect(ui->buttonAdd, &QPushButton::clicked, this, &Taschenrechner::binary_operation_pressed);
	connect(ui->buttonSub, &QPushButton::clicked, this, &Taschenrechner::binary_operation_pressed);
	connect(ui->buttonDivide, &QPushButton::clicked, this, &Taschenrechner::binary_operation_pressed);
	connect(ui->buttonMulti, &QPushButton::clicked, this, &Taschenrechner::binary_operation_pressed);

	// Verbindung des = Buttons mit dem Slot equals_pressed()
	connect(ui->buttonEqual, &QPushButton::clicked, this, &Taschenrechner::equals_pressed);

	// Verbindung des Löschen-Buttons mit dem Slot clear_pressed()
	connect(ui->buttonClear, &QPushButton::clicked, this, &Taschenrechner::clear_pressed);
}

Taschenrechner::~Taschenrechner()
{
	delete ui;
}

void Taschenrechner::digit_pressed()
{




	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (!button)
	{
		qDebug() << "digit_pressed: sender is not a QPushButton";
		return;
	}

	QString buttonValue = button->text();
	QString displayValue = ui->display->text();

	if (buttonValue == ".") 
	{
		if (!displayValue.contains("."))
		{
			ui->display->setText(displayValue + buttonValue);
		}
		return;
	}

	double labelNumber;

	if ((ui->display->text().contains("+") ||
		ui->display->text().contains("-") ||
		ui->display->text().contains("X") ||
		ui->display->text().contains("/")) && !userIsTypingSecondNumber)
	{
		labelNumber = button->text().toDouble();
		userIsTypingSecondNumber = true;
		ui->display->setText(QString::number(labelNumber));
	}
	else
	{
		if (ui->display->text().contains(".") && button->text() == "0")
		{
			labelNumber = ui->display->text().toDouble() * 10.0;
		}
		else
		{
			labelNumber = (ui->display->text() + button->text()).toDouble();
		}

		ui->display->setText(QString::number(labelNumber));
	}
}

void Taschenrechner::binary_operation_pressed()
{
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	currentOperation = button->text();
	firstNumber = ui->display->text().toDouble();

	ui->display->setText(QString(currentOperation));
}

void Taschenrechner::equals_pressed()
{
	secondNumber = ui->display->text().toDouble();

	double result = 0.0;

	if (currentOperation == "+")
	{
		result = firstNumber + secondNumber;
	}
	else if (currentOperation == "-")
	{
		result = firstNumber - secondNumber;
	}
	else if (currentOperation == "X")
	{
		result = firstNumber * secondNumber;
	}
	else if (currentOperation == "/")
	{
		if (secondNumber == 0)
		{
			QMessageBox::warning(this, "Division durch Null", "Division by zero not allowed!");
			return;
		}
		result = firstNumber / secondNumber;
	}

	ui->display->setText(QString::number(result));
	userIsTypingSecondNumber = false;
}

void Taschenrechner::clear_pressed()
{
	ui->display->setText("");
	firstNumber = 0.0;
	secondNumber = 0.0;
	currentOperation = "";
	userIsTypingSecondNumber = false;
}


