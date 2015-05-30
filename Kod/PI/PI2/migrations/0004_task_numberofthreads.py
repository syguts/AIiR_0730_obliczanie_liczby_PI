# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('PI2', '0003_remove_donetask_progress'),
    ]

    operations = [
        migrations.AddField(
            model_name='task',
            name='numberOfThreads',
            field=models.IntegerField(default=1),
            preserve_default=True,
        ),
    ]
