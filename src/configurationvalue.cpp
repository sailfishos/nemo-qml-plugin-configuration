/*
 * Copyright (C) 2012-2015 Jolla Ltd.
 * Contact: <robin.burchell@jollamobile.com>
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

#include "configurationvalue.h"

#include <MGConfItem>

ConfigurationValue::ConfigurationValue(QObject *parent)
    : QObject(parent)
    , mItem(0)
{
}

QString ConfigurationValue::key() const
{
    if (!mItem)
        return QString();

    return mItem->key();
}

void ConfigurationValue::setKey(const QString &newKey)
{
    if (newKey == key())
        return;

    // don't emit valueChanged unless absolutely necessary
    QVariant oldValue = value();

    delete mItem;
    if (newKey.isEmpty()) {
        mItem = 0;
    } else {
        mItem = new MGConfItem(newKey, this);
        connect(mItem, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));
    }

    emit keyChanged();
    if (oldValue != value())
        emit valueChanged();
}

QVariant ConfigurationValue::value() const
{
    if (!mItem)
        return mDefaultValue;

    return mItem->value(mDefaultValue);
}

void ConfigurationValue::setValue(const QVariant &value)
{
    if (mItem)
        mItem->set(value); // TODO: setValue once we change MGConfItem API
    // MGConfItem will emit valueChanged for us
}

QVariant ConfigurationValue::defaultValue() const
{
    return mDefaultValue;
}

void ConfigurationValue::setDefaultValue(const QVariant &value)
{
    if (mDefaultValue == value) {
        return;
    }

    QVariant oldValue = this->value();
    mDefaultValue = value;
    emit defaultValueChanged();

    // if changing the default changed the value, emit valueChanged
    if (this->value() != oldValue)
        emit valueChanged();
}

void ConfigurationValue::sync()
{
    if (mItem) {
        mItem->sync();
    }
}
