#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "Bridge.h"
#include "ExceptionRangeDialog.h"

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    void SaveSettings();

private slots:
    //General
    void on_btnSave_clicked();
    //Event tab
    void on_chkSystemBreakpoint_stateChanged(int arg1);
    void on_chkTlsCallbacks_stateChanged(int arg1);
    void on_chkEntryBreakpoint_stateChanged(int arg1);
    void on_chkDllEntry_stateChanged(int arg1);
    void on_chkThreadEntry_stateChanged(int arg1);
    void on_chkDllLoad_stateChanged(int arg1);
    void on_chkDllUnload_stateChanged(int arg1);
    void on_chkThreadStart_stateChanged(int arg1);
    void on_chkThreadEnd_stateChanged(int arg1);
    void on_chkDebugStrings_stateChanged(int arg1);
    //Engine tab
    void on_radioUnsigned_clicked();
    void on_radioSigned_clicked();
    void on_radioInt3Short_clicked();
    void on_radioInt3Long_clicked();
    void on_radioUd2_clicked();
    void on_chkUndecorateSymbolNames_stateChanged(int arg1);
    //Exception tab
    void on_btnAddRange_clicked();
    void on_btnDeleteRange_clicked();
    void on_btnAddLast_clicked();

private:
    //enums
    enum CalcType
    {
        calc_signed=0,
        calc_unsigned=1
    };

    enum BreakpointType
    {
        break_int3short=0,
        break_int3long=1,
        break_ud2=2
    };

    //structures
    struct RangeStruct
    {
        unsigned long start;
        unsigned long end;
    };

    struct RangeStructLess
    {
        bool operator()(const RangeStruct a, const RangeStruct b) const
        {
            return a.start < b.start;
        }
    };

    struct SettingsStruct
    {
        //Event Tab
        bool eventSystemBreakpoint;
        bool eventTlsCallbacks;
        bool eventEntryBreakpoint;
        bool eventDllEntry;
        bool eventThreadEntry;
        bool eventDllLoad;
        bool eventDllUnload;
        bool eventThreadStart;
        bool eventThreadEnd;
        bool eventDebugStrings;
        //Engine Tab
        CalcType engineCalcType;
        BreakpointType engineBreakpointType;
        bool engineUndecorateSymbolNames;
        //Exception Tab
        QList<RangeStruct>* exceptionRanges;
    };

    //variables
    Ui::SettingsDialog *ui;
    SettingsStruct settings;
    QList<RangeStruct> realExceptionRanges;

    //functions
    void GetSettingBool(const char* section, const char* name, bool* set);
    Qt::CheckState bool2check(bool checked);
    void LoadSettings();
    void AddRangeToList(RangeStruct range);
};

#endif // SETTINGSDIALOG_H
