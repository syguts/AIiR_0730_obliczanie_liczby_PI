# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('PI', '0008_task_userid'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='task',
            name='temporary_text',
        ),
        migrations.AddField(
            model_name='task',
            name='numberOfPoints',
            field=models.IntegerField(default=0),
            preserve_default=True,
        ),
    ]
