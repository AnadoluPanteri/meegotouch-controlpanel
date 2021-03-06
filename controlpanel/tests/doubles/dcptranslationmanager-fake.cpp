/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcptranslationmanager.h"

#include "dcpappletmetadata.h"

#include <QString>
#include <QSet>

class DcpTranslationManagerPriv {
public:
    DcpTranslationManagerPriv();
    QSet<QString> loadedTranslations;
    static DcpTranslationManager* instance;
};

DcpTranslationManager* DcpTranslationManagerPriv::instance = 0;

DcpTranslationManagerPriv::DcpTranslationManagerPriv ()
{
}

DcpTranslationManager::DcpTranslationManager (): priv(new DcpTranslationManagerPriv())
{
}

DcpTranslationManager::~DcpTranslationManager()
{
    delete priv;
    DcpTranslationManagerPriv::instance = 0;
}

void
DcpTranslationManager::retranslate ()
{
}

bool
DcpTranslationManager::loadAppletTranslation (
        MLocale                &,
        const DcpAppletMetadata  *metadata)
{
    QStringList catalogList = metadata->translationCatalogs();
    priv->loadedTranslations.unite(catalogList.toSet());
    return true;
}

void
DcpTranslationManager::ensureTranslationsAreLoaded(const DcpAppletMetadataList& list)
{
    foreach (DcpAppletMetadata* metadata, list) {
        ensureTranslationLoaded(metadata);
    }
}

void
DcpTranslationManager::ensureTranslationLoaded(DcpAppletMetadata* metadata)
{
    QStringList catalogList = metadata->translationCatalogs();
    priv->loadedTranslations.unite(catalogList.toSet());
}

void
DcpTranslationManager::ensureTranslationsAreLoaded(const QStringList &catalogs)
{
    priv->loadedTranslations.unite(catalogs.toSet());
}


DcpTranslationManager*
DcpTranslationManager::instance()
{
    if (DcpTranslationManagerPriv::instance == NULL)
    {
        DcpTranslationManagerPriv::instance = new DcpTranslationManager();
    }
    return DcpTranslationManagerPriv::instance;
}

bool
DcpTranslationManager::eventFilter(QObject *obj, QEvent *event)
{
    return QObject::eventFilter(obj, event);
}
