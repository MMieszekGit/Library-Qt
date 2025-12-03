#include "inputUtils.h"

bool verifyIntInput(const QString& value, const int min_range, const int max_range) {
    bool isNumber;
    int number = value.trimmed().toInt(&isNumber);
    if (!isNumber) { return false; }
    if (number < min_range || number > max_range) { return false; }
    return true;
}

bool verifyEmailInput(const QString& value) {
    return value.contains("@");
}

QString chronoToQDate(const std::chrono::year_month_day ymd) {
    int year = int(ymd.year());
    unsigned month = unsigned(ymd.month());
    unsigned day = unsigned(ymd.day());
    return QDate(year, month, day).toString("yyyy-MM-dd");
}
