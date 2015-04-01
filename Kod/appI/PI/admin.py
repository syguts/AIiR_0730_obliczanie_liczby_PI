from django.contrib import admin
from PI.models import Task
from PI.models import UserProfile

admin.site.register(UserProfile)
admin.site.register(Task)
