/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpretranslator.h"

#include "dcpappletdb.h"
#include "dcpappletmetadata.h"

#include <QString>
#include <QSet>

class DcpRetranslatorPriv {
public:
    DcpRetranslatorPriv();
    QSet<QString> loadedTranslations;
    static DcpRetranslator* instance;
};

DcpRetranslator* DcpRetranslatorPriv::instance = 0;

DcpRetranslatorPriv::DcpRetranslatorPriv ()
{
}

DcpRetranslator::DcpRetranslator (): priv(new DcpRetranslatorPriv())
{
}

void
DcpRetranslator::retranslate ()
{
}

void
DcpRetranslator::loadAppletTranslation (
        DuiLocale                &,
        const DcpAppletMetadata  *metadata)
{
    QString catalog = metadata->translationCatalog();
    priv->loadedTranslations.insert(catalog);
}

void
DcpRetranslator::ensureTranslationsAreLoaded(const DcpAppletMetadataList& list)
{
    foreach (DcpAppletMetadata* metadata, list) {
        ensureTranslationLoaded(metadata);
    }
}

void
DcpRetranslator::ensureTranslationLoaded(DcpAppletMetadata* metadata)
{
    QString catalog = metadata->translationCatalog();
    priv->loadedTranslations.insert(catalog);
}


DcpRetranslator*
DcpRetranslator::instance()
{
    if (DcpRetranslatorPriv::instance == NULL)
    {
        DcpRetranslatorPriv::instance = new DcpRetranslator();
    }
    return DcpRetranslatorPriv::instance;
}

