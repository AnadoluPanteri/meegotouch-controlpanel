/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpappletdb.h"
#include "dcpappletdb_p.h"
#include "dcpappletmetadata.h"
#include "dcpappletobject.h"
#include "dcpretranslator.h"

#include <QDir>
#include <QDebug>
#include <MLocale>
#include <MGConfItem>

#include "dcpdebug.h"

const QString AppletFilter = "*.desktop";
DcpAppletDb* DcpAppletDbPrivate::sm_Instance = 0;

static const QString lastUsedAppletKey = QString(MOSTUSEDCOUNTER_GCONFKEY) +
                                         "/lastUsed";


DcpAppletDbPrivate::DcpAppletDbPrivate():
    hasUniqueMetadata (false)
{

}


DcpAppletDbPrivate::~DcpAppletDbPrivate()
{
}


DcpAppletDb::DcpAppletDb (
        const QString   &pathName,
        const QString   &nameFilter) : d_ptr(new DcpAppletDbPrivate())
{
    if (!pathName.isEmpty())
        addFiles (pathName, nameFilter);

    // try to restore the last used applet:
    QString fileName = MGConfItem(lastUsedAppletKey).value ().toString ();
    if (d_ptr->appletsByFile.contains (fileName)) {
        DcpAppletMetadata::setLastUsed (d_ptr->appletsByFile.value (fileName));
    }
}

DcpAppletDb::~DcpAppletDb()
{
    // store the last used applet:
    DcpAppletMetadata* lastUsed = DcpAppletMetadata::lastUsed();
    if (lastUsed) {
        MGConfItem(lastUsedAppletKey).set (lastUsed->fileName());
    }

    // free up metadatas and applets
    destroyData();

    delete d_ptr;
}


/*!
 *
 * Use this function to get the instance of the DcpAppletDb singleton, by
 * re-using the existing one and initializing it.
 */
DcpAppletDb *
DcpAppletDb::instance (
        const QString   &pathName,
        const QString   &nameFilter)
{
    if (!DcpAppletDbPrivate::sm_Instance) {
        DcpAppletDbPrivate::sm_Instance = new DcpAppletDb (
                pathName, nameFilter);
    }

    return DcpAppletDbPrivate::sm_Instance;
}


void 
DcpAppletDb::destroy ()
{
    if (!DcpAppletDbPrivate::sm_Instance) {
        DCP_WARNING ("There is no instance to destroy.");
        return;
    }

    delete DcpAppletDbPrivate::sm_Instance;
    DcpAppletDbPrivate::sm_Instance = 0;
}

bool
DcpAppletDb::addFile (
        const QString& filename)
{
    if (containsFile(filename) || d_ptr->hasUniqueMetadata)
        return false;

    DcpAppletMetadata *metadata = new DcpAppletMetadata(filename);
    if (metadata->isValid()) {
        if (metadata->isUnique()) {
             d_ptr->appletsByName.clear();
             d_ptr->appletsByFile.clear();
             d_ptr->hasUniqueMetadata = true;
        }
        DCP_DEBUG ("Adding applet name '%s'", DCP_STR (metadata->name()));
        d_ptr->appletsByName[metadata->name()] = metadata;
        d_ptr->appletsByFile[filename] = metadata;
        return true;
    } else {
        metadata->deleteLater();
    }

    return false;
}

QStringList
DcpAppletDb::appletNames() const
{
    return d_ptr->appletsByName.keys();
}

bool
DcpAppletDb::containsFile(const QString& fileName)
{
    return d_ptr->appletsByFile.contains(fileName);
}

bool
DcpAppletDb::containsName(const QString &name)
{
    return d_ptr->appletsByName.contains (name);
}

bool
DcpAppletDb::addPath(const QString &pathName)
{
    if (addFiles (pathName, "*.desktop")) {
        d_ptr->paths.append(pathName);
        return true;
    } else {
        return false;
    }
}

bool
DcpAppletDb::addFiles (
        const QString  &pathName, 
        const QString  &filter)
{
    QStringList nameFilters (filter);
    QDir        appDir (pathName);

    bool success = true;
    appDir.setNameFilters (nameFilters);
    foreach (QString appFile, appDir.entryList (QDir::Files)) {
        DCP_DEBUG ("Adding file '%s'", 
                DCP_STR (appDir.absoluteFilePath(appFile)));
        if (!addFile (appDir.absoluteFilePath(appFile)))
            success = false;
    }

    return success;
}

DcpAppletMetadataList 
DcpAppletDb::list() const
{
    return d_ptr->appletsByFile.values();
}


/*
 * Categories should be ordered by the way it is specified in their
 * desktop files, except the applications category, which should be ordered
 * by the name of the items
 */
static void sortACategory (QList<DcpAppletMetadata*>& filtered,
                           const QString& category)
{
    // FIXME: quick solution, we should remove this magic word and
    //        export the category names (?)
    qSort(filtered.begin(), filtered.end(),
          category == "qtn_sett_main_application" ?
                      DcpAppletMetadata::nameLessThan :
                      DcpAppletMetadata::orderLessThan
         );
}

/*!
 *
 */
DcpAppletMetadataList
DcpAppletDb::listByCategory (
        const QString &category)
{
    QList<DcpAppletMetadata*> filtered;

    foreach (DcpAppletMetadata *item, d_ptr->appletsByFile) {
        if (category.compare (item->category(), Qt::CaseInsensitive) == 0)
            filtered.append (item);

        // FIXME: This should not be done here!
        QString parentName = item->parentName ();
        if (parentName != "" && !item->parent()) {
            item->setParent (d_ptr->appletsByName[parentName]);
        }
    }

    sortACategory (filtered, category);
    return filtered;
}

/*!
 * \param category An array of string pointers with the category names. All
 *   categories with these names will be added.
 * \param n_categories The size of the name array.
 * \param checkFunction If not NULL the function will be called with the
 *   category name of the metadata items and those that are getting false return
 *   value are going to be added too. Used to handle the uncategorized applets.
 */
DcpAppletMetadataList 
DcpAppletDb::listByCategory (
        const char **category,
        int          n_categories,
        checkCategory   checkFunction)
{
    QList<DcpAppletMetadata*> filtered;

    foreach (DcpAppletMetadata *item, d_ptr->appletsByFile) {
        for (int n = 0; n < n_categories && category[n] != 0; ++n) {
            /*
             * We add this item if we asked to include the uncategorized
             * items and this is an uncategorized item or if the item is in the
             * category we are requested for.
             */
            #if 0
            DCP_WARNING ("------------------------------");
            DCP_WARNING ("applet        = %s", DCP_STR(item->name()));
            DCP_WARNING ("category      = %s", DCP_STR(item->category()));
            DCP_WARNING ("checkFunction = %p", checkFunction);
            DCP_WARNING ("checked       = %s", 
                    checkFunction && checkFunction (item->category ()) ?
                    "true" : "false");
            #endif

            if ((checkFunction && !checkFunction (item->category ())) ||
                    !item->category().compare (
                        QString(category[n]), Qt::CaseInsensitive)) {
                //DCP_WARNING ("Adding applet %s", DCP_STR(item->name()));
                filtered.append (item);
                break;
            }
        }

        // FIXME: This should not be done here!
        QString parentName = item->parentName ();
        if (parentName != "" && !item->parent()) {
            item->setParent(d_ptr->appletsByName[parentName]);

        }
    }

    sortACategory (filtered, n_categories > 0 ? category[0] : QString());
    return filtered;
}

DcpAppletMetadataList 
DcpAppletDb::listMostUsed ()
{
    DcpAppletMetadataList mostUsed;
    DcpAppletMetadata* lastUsed = DcpAppletMetadata::lastUsed();

    for (QMap<QString, DcpAppletMetadata*>::iterator iter =
            d_ptr->appletsByName.begin(); iter != d_ptr->appletsByName.end();
            iter++)
    {
        // we skip not used items, and also the last used item
        // (to avoid duplication)
        if (iter.value()->usage() && iter.value() != lastUsed)
            mostUsed.push_back(iter.value());
    }

   qSort (mostUsed.begin(), mostUsed.end(), 
           DcpAppletMetadata::usageGreatherThan);

   // last clicked item should be the first item (see bug NB#169944)
   if (lastUsed) {
        mostUsed.prepend (lastUsed);
   }
   mostUsed = mostUsed.mid (0, DcpApplet::MaxMostUsed);
   return mostUsed;
}


/*!
 * \brief Returns the applet found in the database by its name.
 *
 * FIXME: This is actually a localized name, that is changed when the language
 * settings are changed. This might cause some problems in the future.
 */
DcpAppletObject *
DcpAppletDb::applet (
        const QString &name)
{
    DcpAppletObject *obj = d_ptr->appletObjectsByName.value(name, 0);

    if (!obj)
    {
        DcpAppletMetadata *metadata = d_ptr->appletsByName.value(name, 0);
        if (metadata)
        {
            obj = new DcpAppletObject(metadata);
            d_ptr->appletObjectsByName[name] = obj;
            emit appletLoaded (obj);
        }
        else
            qWarning() << "No such applet:" << name;
    }
    return obj;
}

void 
DcpAppletDb::eraseEntry (
        DcpAppletMetadata *metadata)
{
    d_ptr->appletsByName.remove(metadata->name());
    d_ptr->appletsByFile.remove(metadata->fileName());
    metadata->deleteLater();
}

void 
DcpAppletDb::destroyData ()
{
    DCP_DEBUG ("Destroying all metadata.");
    foreach(DcpAppletMetadata *metadata, d_ptr->appletsByName) {
        delete metadata;
    }
    d_ptr->appletsByName.clear();

    DCP_DEBUG ("Destroying DcpAppletObjects");
    foreach(DcpAppletObject *applet, d_ptr->appletObjectsByName) {
        delete applet;
    }
    d_ptr->appletObjectsByName.clear();
}

