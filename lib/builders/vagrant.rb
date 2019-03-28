module Builders
  class Vagrant < Builder
    TYPE = 'vagrant'

    def rebind(scroll_name)
      Vagrant.new(@scroll.workspace.scroll(scroll_name))
    end

    def build_id
      require 'time'
      d = Time.now
      "#{d.year}.#{d.month}.#{d.day}#{d.hour}#{d.min}#{d.sec}"
    end

    def output_dir
      @scroll.artifact_dir
    end

    def source_tmpl
      @source_tmpl ||= @scroll.root / 'source.yaml.erb'
    end

    def metadata_tmpl
      @metadata_tmpl ||= @scroll.root / 'metadata.yaml.erb'
    end

    def render(tmpl_path)
      require_relative '../util'
      require 'erb'
      require 'yaml'
      YAML.safe_load ERB
        .new(tmpl_path.read, 0, '%')
        .result(binding)
    end

    def source
      @source ||= render(source_tmpl)
    end

    def metadata
      @metadata ||= render(metadata_tmpl)
    end

    def source_path
      Pathname.new(source&.dig('name') || 'source.json')
    end

    def artifact(_)
      @artifact ||= (output_dir / 'output-vagrant' / 'package.box')
    end

    def source_json
      @source_json ||= (output_dir / source_path)
    end

    def metadata_json
      @metadata_json ||= (output_dir / 'metadata.json')
    end

    alias_method :source_erb, :source_tmpl

    def metadata_erb
      @metadata_erb ||= (@scroll.root / 'metadata.yaml.erb')
    end

    def inject(builder_def)
      @inject ||= builder_def
        .merge(
          'output_dir' => artifact(nil).dirname.relative_path_from(output_dir).to_s,
          'skip_add' => false,
          'source_path' => source_path.to_s,
        )
        .freeze
    end
  end
end
