# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('PI', '0005_auto_20150401_2017'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='task',
            name='add_date',
        ),
    ]
