# Generated by Django 5.0.1 on 2024-01-19 20:02

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('nick', '0023_title_role_type_alter_genre_name'),
    ]

    operations = [
        migrations.AddField(
            model_name='title',
            name='cast_members',
            field=models.TextField(blank=True),
        ),
    ]