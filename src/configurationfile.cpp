
/*
 * Copyright (C) 2019 Jolla Ltd. <timur.kristof@jollamobile.com>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Nemo Mobile nor the names of its contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */

#include "configurationfile.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>

ConfigurationFile::ConfigurationFile(QObject *parent)
    : QObject(parent)
    , m_active(true)
    , m_settings(0)
{
}

void ConfigurationFile::reset()
{
    if (!m_active || m_fileName.isEmpty()) {
        m_settings.reset(0);
        emit fileChanged();
        return;
    }

    QSettings *settings = new QSettings(m_fileName, QSettings::IniFormat);
    m_settings.reset(settings);
    emit fileChanged();
}

bool ConfigurationFile::active() const
{
    return m_active;
}

void ConfigurationFile::setActive(bool value)
{
    if (value != m_active) {
        m_active = value;
        reset();
    }
}

QString ConfigurationFile::fileName() const
{
    return m_fileName;
}

void ConfigurationFile::setFileName(const QString &value)
{
    if (value != m_fileName) {
        m_fileName = value;
        reset();
    }
}

QVariant ConfigurationFile::read(const QString &key, QVariant defaultValue)
{
    if (m_settings.isNull()) {
        return QVariant();
    }

    return m_settings->value(key, defaultValue);
}

bool ConfigurationFile::write(const QString &key, QVariant value)
{
    if (m_settings.isNull()) {
        return false;
    }

    m_settings->setValue(key, value);
    emit fileChanged();
    return true;
}
