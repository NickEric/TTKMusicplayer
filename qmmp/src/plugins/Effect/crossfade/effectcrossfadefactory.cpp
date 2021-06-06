#include "effectcrossfadefactory.h"
#include "settingsdialog.h"
#include "crossfadeplugin.h"

const EffectProperties EffectCrossfadeFactory::properties() const
{
    EffectProperties properties;
    properties.name = tr("Crossfade Plugin");
    properties.shortName = "crossfade";
    properties.hasSettings = true;
    properties.priority = EffectProperties::EFFECT_PRIORITY_LOW;
    return properties;
}

Effect *EffectCrossfadeFactory::create()
{
    return new CrossfadePlugin();
}

void EffectCrossfadeFactory::showSettings(QWidget *parent)
{
    SettingsDialog *dialog = new SettingsDialog(parent);
    dialog->show();
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
#include <QtPlugin>
Q_EXPORT_PLUGIN2(crossfade, EffectCrossfadeFactory)
#endif
