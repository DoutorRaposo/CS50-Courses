# Generated by Django 4.2.6 on 2024-01-09 21:43

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('nick', '0001_initial'),
    ]

    operations = [
        migrations.RenameModel(
            old_name='Movies',
            new_name='Movie',
        ),
    ]