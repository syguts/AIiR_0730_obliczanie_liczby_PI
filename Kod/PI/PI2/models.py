from django.db import models
from django.contrib.auth.models import User
import django.contrib.auth
from django.template.defaultfilters import default
from django.utils import timezone


#klasa dla Histori zadan
class Task(models.Model):
    userID = models.ForeignKey('auth.User')
    numberOfPoints = models.BigIntegerField(default=0)
    numberOfThreads = models.IntegerField(default=1)
    add_date = models.DateTimeField(default=timezone.now)
    
    
class DoneTask(models.Model):
    userID = models.ForeignKey('auth.User')
    numberOfPoints = models.BigIntegerField(default=0)
    add_date = models.DateTimeField(default=timezone.now)
    value = models.TextField();
    


class UserProfile(models.Model):
    # This line is required. Links UserProfile to a User model instance.
    user = models.OneToOneField(User)

    # The additional attributes we wish to include.
    #website = models.URLField(blank=True)
   # picture = models.ImageField(upload_to='profile_images', blank=True)

    # Override the __unicode__() method to return out something meaningful!
    def __unicode__(self):
        return self.user.username

