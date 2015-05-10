from django.contrib import admin
from PI2.models import Task
from PI2.models import UserProfile
from PI2.models import DoneTask

admin.site.register(UserProfile)
admin.site.register(Task)
admin.site.register(DoneTask)
