
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

#include "configurationfilevalue.h"
#include "configurationfile.h"
#include <QtCore/QDebug>

ConfigurationFileValue::ConfigurationFileValue(QObject *parent)
    : QObject(parent)
    , m_configurationFile(0)
{
}

QString ConfigurationFileValue::key() const
{
    return m_key;
}

void ConfigurationFileValue::setKey(const QString &key)
{
    if (key != m_key) {
        m_key = key;
        emit keyChanged();
    }
}

QVariant ConfigurationFileValue::value() const
{
    if (!m_configurationFile || m_key.isEmpty()) {
        return QVariant();
    }

    QVariant v = m_configurationFile->read(m_key, m_defaultValue);
    return v;
}

void ConfigurationFileValue::setValue(const QVariant &valueToWrite)
{
    if (!m_configurationFile) {
        qWarning() << "Please set configurationFile before trying to set a value.";
        return;
    }

    if (m_key.isEmpty()) {
        qWarning() << "Please set key to a non-empty string before trying to set a value.";
        return;
    }

    if (value() == valueToWrite) {
        return;
    }

    m_configurationFile->write(m_key, valueToWrite);
    // No need to emit valueChanged, ConfigurationFile will emit fileChanged which we are connected to
}

QVariant ConfigurationFileValue::defaultValue() const
{
    return m_defaultValue;
}

void ConfigurationFileValue::setDefaultValue(const QVariant &value)
{
    if (m_defaultValue != value) {
        m_defaultValue = value;
        emit defaultValueChanged();
        emit valueChanged();
    }
}

ConfigurationFile *ConfigurationFileValue::configurationFile() const
{
    return m_configurationFile;
}

void ConfigurationFileValue::setConfigurationFile(ConfigurationFile *file)
{
    if (m_configurationFile != file) {
        if (m_configurationFile) {
            disconnect(m_configurationFile, &ConfigurationFile::fileChanged, this, &ConfigurationFileValue::valueChanged);
        }

        m_configurationFile = file;
        connect(m_configurationFile, &ConfigurationFile::fileChanged, this, &ConfigurationFileValue::valueChanged);
        emit configurationFileChanged();
        emit valueChanged();
    }
}
