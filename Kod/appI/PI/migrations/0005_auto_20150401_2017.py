# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('PI', '0004_auto_20150331_1938'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='userprofile',
            name='picture',
        ),
        migrations.RemoveField(
            model_name='userprofile',
            name='website',
        ),
    ]
