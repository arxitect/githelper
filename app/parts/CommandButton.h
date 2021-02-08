/****************************************************************************
 *
 * This file is part of the Git Helper application.
 *
 * Standard QPushButton Widget with children
 *
****************************************************************************/
#ifndef GIT_HELPER_COMMANDBUTTON_H
#define GIT_HELPER_COMMANDBUTTON_H

#include <QtWidgets/QPushButton>

namespace App {

class CommandButton : public QPushButton {
Q_OBJECT
public:
    CommandButton *childButton;

    explicit CommandButton(const QString &text, QWidget *pwgt = nullptr) : QPushButton(text, pwgt), childButton(nullptr) {};
};

}
#endif //GIT_HELPER_COMMANDBUTTON_H
