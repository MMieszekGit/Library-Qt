#pragma once

#include <string>
#include <QString>
#include <QDateTime>
#include <chrono>

bool verifyIntInput(const QString& value, int min_range = 1, int max_range = 9999);
bool verifyEmailInput(const QString& email);
QString chronoToQDate(const std::chrono::year_month_day ymd);
