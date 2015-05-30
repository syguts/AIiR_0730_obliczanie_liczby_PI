# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('PI2', '0002_donetask_progress'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='donetask',
            name='progress',
        ),
    ]
