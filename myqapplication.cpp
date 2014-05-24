

#include <objc/runtime.h>
#include <objc/message.h>

#include <QtGlobal>

#include "myqapplication.h"

bool dockClickHandler(id self,SEL _cmd,...) {
    Q_UNUSED(self)
    Q_UNUSED(_cmd)
    ((MyQApplication*)qApp)->onClickOnDock();
    return true;
}



MyQApplication::MyQApplication(int & argc, char ** argv) : QApplication(argc, argv) {

    void* cls = objc_getClass("NSApplication");
    SEL sharedApplication = sel_registerName("sharedApplication");
    objc_object* appInst = objc_msgSend((objc_object*)cls ,sharedApplication);

    if(appInst != NULL)
    {
        objc_object* delegate = objc_msgSend(appInst, sel_registerName("delegate"));
        objc_object* delClass = objc_msgSend(delegate,  sel_registerName("class"));
        //const char* tst = class_getName(delClass->isa);
        bool test = class_addMethod((objc_class*)delClass, sel_registerName("applicationShouldHandleReopen:hasVisibleWindows:"), (IMP)dockClickHandler,"B@:");

        if (!test)
        {
            // failed to register handler...
        }
    }
}

void MyQApplication::onClickOnDock() {
  emit dockIconClicked();
}
