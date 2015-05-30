# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('PI2', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='donetask',
            name='progress',
            field=models.TextField(default=0),
            preserve_default=False,
        ),
    ]
