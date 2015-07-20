/*
 * Copyright (C) 2014 Jolla Mobile <andrew.den.exter@jollamobile.com>
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

#include "configurationgroup.h"

ConfigurationGroup::ConfigurationGroup(QObject *parent)
    : MDConfGroup(parent, BindProperties)
{
}

ConfigurationGroup::~ConfigurationGroup()
{
}

void ConfigurationGroup::classBegin()
{
}

void ConfigurationGroup::componentComplete()
{
    resolveMetaObject(staticMetaObject.propertyCount());
}

QQmlListProperty<QObject> ConfigurationGroup::data()
{
    return QQmlListProperty<QObject>(this, 0, data_append, data_count, data_at, data_clear);
}

void ConfigurationGroup::data_append(QQmlListProperty<QObject> *property, QObject *value)
{
    ConfigurationGroup *settings = static_cast<ConfigurationGroup *>(property->object);
    settings->m_data.append(value);
    if (MDConfGroup *child = qobject_cast<MDConfGroup *>(value))
        child->setScope(settings);
}

QObject *ConfigurationGroup::data_at(QQmlListProperty<QObject> *property, int index)
{
    return static_cast<ConfigurationGroup *>(property->object)->m_data.at(index);
}

int ConfigurationGroup::data_count(QQmlListProperty<QObject> *property)
{
    return static_cast<ConfigurationGroup *>(property->object)->m_data.count();
}

void ConfigurationGroup::data_clear(QQmlListProperty<QObject> *property)
{
    ConfigurationGroup *settings = static_cast<ConfigurationGroup *>(property->object);
    QList<QObject *> data = settings->m_data;
    settings->m_data.clear();

    foreach (QObject *object, data) {
        ConfigurationGroup *group = qobject_cast<ConfigurationGroup *>(object);
        if (group && group->scope() == settings) {
            group->setScope(0);
        }
    }
}
