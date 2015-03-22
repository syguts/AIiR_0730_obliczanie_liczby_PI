# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations
import datetime


class Migration(migrations.Migration):

    dependencies = [
        ('PI', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='task',
            name='add_date',
            field=models.DateTimeField(default=datetime.datetime(2015, 3, 22, 18, 4, 51, 853660), verbose_name=b'date added'),
            preserve_default=False,
        ),
    ]
